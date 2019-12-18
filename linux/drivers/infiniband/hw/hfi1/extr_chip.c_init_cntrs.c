#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct hfi1_pportdata {void* scntrs; void* cntrs; } ;
struct hfi1_devdata {size_t cntrnameslen; char* cntrnames; int num_rcv_contexts; size_t portcntrnameslen; char* portcntrnames; int num_pports; int /*<<< orphan*/  synth_stats_timer; int /*<<< orphan*/  update_cntr_work; int /*<<< orphan*/  update_cntr_wq; int /*<<< orphan*/  unit; scalar_t__ nportcntrs; void* scntrs; scalar_t__ ndevcntrs; void* cntrs; } ;
struct TYPE_4__ {int flags; char* name; scalar_t__ offset; } ;
struct TYPE_3__ {int flags; char* name; scalar_t__ offset; } ;

/* Variables and functions */
 int CNTR_32BIT ; 
 int CNTR_DISABLED ; 
 int CNTR_SDMA ; 
 int CNTR_VL ; 
 int C_MAX_NAME ; 
 int C_RCV_HDR_OVF_FIRST ; 
 int C_RCV_HDR_OVF_LAST ; 
 int C_VL_COUNT ; 
 int DEV_CNTR_LAST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PORT_CNTR_LAST ; 
 int SYNTH_CNT_TIME ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chip_sdma_engines (struct hfi1_devdata*) ; 
 TYPE_2__* dev_cntrs ; 
 int /*<<< orphan*/  do_update_synth_timer ; 
 int /*<<< orphan*/  free_cntrs (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_dbg_early (char*,char*) ; 
 scalar_t__ init_cpu_counters (struct hfi1_devdata*) ; 
 scalar_t__ jiffies ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int const) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ num_driver_cntrs ; 
 TYPE_1__* port_cntrs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int const strlen (char const*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_synth_timer ; 
 int vl_from_idx (int) ; 

__attribute__((used)) static int init_cntrs(struct hfi1_devdata *dd)
{
	int i, rcv_ctxts, j;
	size_t sz;
	char *p;
	char name[C_MAX_NAME];
	struct hfi1_pportdata *ppd;
	const char *bit_type_32 = ",32";
	const int bit_type_32_sz = strlen(bit_type_32);
	u32 sdma_engines = chip_sdma_engines(dd);

	/* set up the stats timer; the add_timer is done at the end */
	timer_setup(&dd->synth_stats_timer, update_synth_timer, 0);

	/***********************/
	/* per device counters */
	/***********************/

	/* size names and determine how many we have*/
	dd->ndevcntrs = 0;
	sz = 0;

	for (i = 0; i < DEV_CNTR_LAST; i++) {
		if (dev_cntrs[i].flags & CNTR_DISABLED) {
			hfi1_dbg_early("\tSkipping %s\n", dev_cntrs[i].name);
			continue;
		}

		if (dev_cntrs[i].flags & CNTR_VL) {
			dev_cntrs[i].offset = dd->ndevcntrs;
			for (j = 0; j < C_VL_COUNT; j++) {
				snprintf(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name, vl_from_idx(j));
				sz += strlen(name);
				/* Add ",32" for 32-bit counters */
				if (dev_cntrs[i].flags & CNTR_32BIT)
					sz += bit_type_32_sz;
				sz++;
				dd->ndevcntrs++;
			}
		} else if (dev_cntrs[i].flags & CNTR_SDMA) {
			dev_cntrs[i].offset = dd->ndevcntrs;
			for (j = 0; j < sdma_engines; j++) {
				snprintf(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name, j);
				sz += strlen(name);
				/* Add ",32" for 32-bit counters */
				if (dev_cntrs[i].flags & CNTR_32BIT)
					sz += bit_type_32_sz;
				sz++;
				dd->ndevcntrs++;
			}
		} else {
			/* +1 for newline. */
			sz += strlen(dev_cntrs[i].name) + 1;
			/* Add ",32" for 32-bit counters */
			if (dev_cntrs[i].flags & CNTR_32BIT)
				sz += bit_type_32_sz;
			dev_cntrs[i].offset = dd->ndevcntrs;
			dd->ndevcntrs++;
		}
	}

	/* allocate space for the counter values */
	dd->cntrs = kcalloc(dd->ndevcntrs + num_driver_cntrs, sizeof(u64),
			    GFP_KERNEL);
	if (!dd->cntrs)
		goto bail;

	dd->scntrs = kcalloc(dd->ndevcntrs, sizeof(u64), GFP_KERNEL);
	if (!dd->scntrs)
		goto bail;

	/* allocate space for the counter names */
	dd->cntrnameslen = sz;
	dd->cntrnames = kmalloc(sz, GFP_KERNEL);
	if (!dd->cntrnames)
		goto bail;

	/* fill in the names */
	for (p = dd->cntrnames, i = 0; i < DEV_CNTR_LAST; i++) {
		if (dev_cntrs[i].flags & CNTR_DISABLED) {
			/* Nothing */
		} else if (dev_cntrs[i].flags & CNTR_VL) {
			for (j = 0; j < C_VL_COUNT; j++) {
				snprintf(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name,
					 vl_from_idx(j));
				memcpy(p, name, strlen(name));
				p += strlen(name);

				/* Counter is 32 bits */
				if (dev_cntrs[i].flags & CNTR_32BIT) {
					memcpy(p, bit_type_32, bit_type_32_sz);
					p += bit_type_32_sz;
				}

				*p++ = '\n';
			}
		} else if (dev_cntrs[i].flags & CNTR_SDMA) {
			for (j = 0; j < sdma_engines; j++) {
				snprintf(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name, j);
				memcpy(p, name, strlen(name));
				p += strlen(name);

				/* Counter is 32 bits */
				if (dev_cntrs[i].flags & CNTR_32BIT) {
					memcpy(p, bit_type_32, bit_type_32_sz);
					p += bit_type_32_sz;
				}

				*p++ = '\n';
			}
		} else {
			memcpy(p, dev_cntrs[i].name, strlen(dev_cntrs[i].name));
			p += strlen(dev_cntrs[i].name);

			/* Counter is 32 bits */
			if (dev_cntrs[i].flags & CNTR_32BIT) {
				memcpy(p, bit_type_32, bit_type_32_sz);
				p += bit_type_32_sz;
			}

			*p++ = '\n';
		}
	}

	/*********************/
	/* per port counters */
	/*********************/

	/*
	 * Go through the counters for the overflows and disable the ones we
	 * don't need. This varies based on platform so we need to do it
	 * dynamically here.
	 */
	rcv_ctxts = dd->num_rcv_contexts;
	for (i = C_RCV_HDR_OVF_FIRST + rcv_ctxts;
	     i <= C_RCV_HDR_OVF_LAST; i++) {
		port_cntrs[i].flags |= CNTR_DISABLED;
	}

	/* size port counter names and determine how many we have*/
	sz = 0;
	dd->nportcntrs = 0;
	for (i = 0; i < PORT_CNTR_LAST; i++) {
		if (port_cntrs[i].flags & CNTR_DISABLED) {
			hfi1_dbg_early("\tSkipping %s\n", port_cntrs[i].name);
			continue;
		}

		if (port_cntrs[i].flags & CNTR_VL) {
			port_cntrs[i].offset = dd->nportcntrs;
			for (j = 0; j < C_VL_COUNT; j++) {
				snprintf(name, C_MAX_NAME, "%s%d",
					 port_cntrs[i].name, vl_from_idx(j));
				sz += strlen(name);
				/* Add ",32" for 32-bit counters */
				if (port_cntrs[i].flags & CNTR_32BIT)
					sz += bit_type_32_sz;
				sz++;
				dd->nportcntrs++;
			}
		} else {
			/* +1 for newline */
			sz += strlen(port_cntrs[i].name) + 1;
			/* Add ",32" for 32-bit counters */
			if (port_cntrs[i].flags & CNTR_32BIT)
				sz += bit_type_32_sz;
			port_cntrs[i].offset = dd->nportcntrs;
			dd->nportcntrs++;
		}
	}

	/* allocate space for the counter names */
	dd->portcntrnameslen = sz;
	dd->portcntrnames = kmalloc(sz, GFP_KERNEL);
	if (!dd->portcntrnames)
		goto bail;

	/* fill in port cntr names */
	for (p = dd->portcntrnames, i = 0; i < PORT_CNTR_LAST; i++) {
		if (port_cntrs[i].flags & CNTR_DISABLED)
			continue;

		if (port_cntrs[i].flags & CNTR_VL) {
			for (j = 0; j < C_VL_COUNT; j++) {
				snprintf(name, C_MAX_NAME, "%s%d",
					 port_cntrs[i].name, vl_from_idx(j));
				memcpy(p, name, strlen(name));
				p += strlen(name);

				/* Counter is 32 bits */
				if (port_cntrs[i].flags & CNTR_32BIT) {
					memcpy(p, bit_type_32, bit_type_32_sz);
					p += bit_type_32_sz;
				}

				*p++ = '\n';
			}
		} else {
			memcpy(p, port_cntrs[i].name,
			       strlen(port_cntrs[i].name));
			p += strlen(port_cntrs[i].name);

			/* Counter is 32 bits */
			if (port_cntrs[i].flags & CNTR_32BIT) {
				memcpy(p, bit_type_32, bit_type_32_sz);
				p += bit_type_32_sz;
			}

			*p++ = '\n';
		}
	}

	/* allocate per port storage for counter values */
	ppd = (struct hfi1_pportdata *)(dd + 1);
	for (i = 0; i < dd->num_pports; i++, ppd++) {
		ppd->cntrs = kcalloc(dd->nportcntrs, sizeof(u64), GFP_KERNEL);
		if (!ppd->cntrs)
			goto bail;

		ppd->scntrs = kcalloc(dd->nportcntrs, sizeof(u64), GFP_KERNEL);
		if (!ppd->scntrs)
			goto bail;
	}

	/* CPU counters need to be allocated and zeroed */
	if (init_cpu_counters(dd))
		goto bail;

	dd->update_cntr_wq = alloc_ordered_workqueue("hfi1_update_cntr_%d",
						     WQ_MEM_RECLAIM, dd->unit);
	if (!dd->update_cntr_wq)
		goto bail;

	INIT_WORK(&dd->update_cntr_work, do_update_synth_timer);

	mod_timer(&dd->synth_stats_timer, jiffies + HZ * SYNTH_CNT_TIME);
	return 0;
bail:
	free_cntrs(dd);
	return -ENOMEM;
}