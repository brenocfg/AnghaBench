#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct hfi1_pportdata {struct hfi1_devdata* dd; } ;
struct TYPE_7__ {scalar_t__ nctxt_extra; unsigned int ngroups; unsigned int group_size; } ;
struct hfi1_devdata {scalar_t__ num_rcv_contexts; scalar_t__ first_dyn_alloc_ctxt; unsigned int n_krcv_queues; TYPE_3__ rcv_entries; } ;
struct TYPE_8__ {scalar_t__ count; scalar_t__ size; int /*<<< orphan*/  rcvtid_size; void* rcvtids; void* buffers; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue_head; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue_head; } ;
struct hfi1_ctxtdata {int numa_id; unsigned int rcv_array_groups; unsigned int eager_base; void* opstats; TYPE_4__ egrbufs; int /*<<< orphan*/  ctxt; scalar_t__ rcvhdrqentsize; scalar_t__ rhf_offset; int /*<<< orphan*/  rcvhdrq_cnt; TYPE_2__ rarr_queue; TYPE_1__ flow_queue; int /*<<< orphan*/  exp_lock; int /*<<< orphan*/  exp_mutex; int /*<<< orphan*/  rhf_rcv_function_map; struct hfi1_devdata* dd; struct hfi1_pportdata* ppd; int /*<<< orphan*/  qp_wait_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFI1_MAX_EAGER_BUFFER_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_EAGER_ENTRIES ; 
 int /*<<< orphan*/  PROC ; 
 scalar_t__ __roundup_pow_of_two (scalar_t__) ; 
 int allocate_rcd_index (struct hfi1_devdata*,struct hfi1_ctxtdata*,unsigned int*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ eager_buffer_size ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  hfi1_exp_tid_group_init (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_free_ctxt (struct hfi1_ctxtdata*) ; 
 scalar_t__ hfi1_hdrq_entsize ; 
 int /*<<< orphan*/  hfi1_kern_init_ctxt_generations (struct hfi1_ctxtdata*) ; 
 scalar_t__ hfi1_max_mtu ; 
 unsigned int hfi1_rcvarr_split ; 
 void* kcalloc_node (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct hfi1_ctxtdata*) ; 
 void* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  normal_rhf_rcv_functions ; 
 int /*<<< orphan*/  rcvhdrcnt ; 
 scalar_t__ round_down (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hfi1_create_ctxtdata(struct hfi1_pportdata *ppd, int numa,
			 struct hfi1_ctxtdata **context)
{
	struct hfi1_devdata *dd = ppd->dd;
	struct hfi1_ctxtdata *rcd;
	unsigned kctxt_ngroups = 0;
	u32 base;

	if (dd->rcv_entries.nctxt_extra >
	    dd->num_rcv_contexts - dd->first_dyn_alloc_ctxt)
		kctxt_ngroups = (dd->rcv_entries.nctxt_extra -
			 (dd->num_rcv_contexts - dd->first_dyn_alloc_ctxt));
	rcd = kzalloc_node(sizeof(*rcd), GFP_KERNEL, numa);
	if (rcd) {
		u32 rcvtids, max_entries;
		u16 ctxt;
		int ret;

		ret = allocate_rcd_index(dd, rcd, &ctxt);
		if (ret) {
			*context = NULL;
			kfree(rcd);
			return ret;
		}

		INIT_LIST_HEAD(&rcd->qp_wait_list);
		hfi1_exp_tid_group_init(rcd);
		rcd->ppd = ppd;
		rcd->dd = dd;
		rcd->numa_id = numa;
		rcd->rcv_array_groups = dd->rcv_entries.ngroups;
		rcd->rhf_rcv_function_map = normal_rhf_rcv_functions;

		mutex_init(&rcd->exp_mutex);
		spin_lock_init(&rcd->exp_lock);
		INIT_LIST_HEAD(&rcd->flow_queue.queue_head);
		INIT_LIST_HEAD(&rcd->rarr_queue.queue_head);

		hfi1_cdbg(PROC, "setting up context %u\n", rcd->ctxt);

		/*
		 * Calculate the context's RcvArray entry starting point.
		 * We do this here because we have to take into account all
		 * the RcvArray entries that previous context would have
		 * taken and we have to account for any extra groups assigned
		 * to the static (kernel) or dynamic (vnic/user) contexts.
		 */
		if (ctxt < dd->first_dyn_alloc_ctxt) {
			if (ctxt < kctxt_ngroups) {
				base = ctxt * (dd->rcv_entries.ngroups + 1);
				rcd->rcv_array_groups++;
			} else {
				base = kctxt_ngroups +
					(ctxt * dd->rcv_entries.ngroups);
			}
		} else {
			u16 ct = ctxt - dd->first_dyn_alloc_ctxt;

			base = ((dd->n_krcv_queues * dd->rcv_entries.ngroups) +
				kctxt_ngroups);
			if (ct < dd->rcv_entries.nctxt_extra) {
				base += ct * (dd->rcv_entries.ngroups + 1);
				rcd->rcv_array_groups++;
			} else {
				base += dd->rcv_entries.nctxt_extra +
					(ct * dd->rcv_entries.ngroups);
			}
		}
		rcd->eager_base = base * dd->rcv_entries.group_size;

		rcd->rcvhdrq_cnt = rcvhdrcnt;
		rcd->rcvhdrqentsize = hfi1_hdrq_entsize;
		rcd->rhf_offset =
			rcd->rcvhdrqentsize - sizeof(u64) / sizeof(u32);
		/*
		 * Simple Eager buffer allocation: we have already pre-allocated
		 * the number of RcvArray entry groups. Each ctxtdata structure
		 * holds the number of groups for that context.
		 *
		 * To follow CSR requirements and maintain cacheline alignment,
		 * make sure all sizes and bases are multiples of group_size.
		 *
		 * The expected entry count is what is left after assigning
		 * eager.
		 */
		max_entries = rcd->rcv_array_groups *
			dd->rcv_entries.group_size;
		rcvtids = ((max_entries * hfi1_rcvarr_split) / 100);
		rcd->egrbufs.count = round_down(rcvtids,
						dd->rcv_entries.group_size);
		if (rcd->egrbufs.count > MAX_EAGER_ENTRIES) {
			dd_dev_err(dd, "ctxt%u: requested too many RcvArray entries.\n",
				   rcd->ctxt);
			rcd->egrbufs.count = MAX_EAGER_ENTRIES;
		}
		hfi1_cdbg(PROC,
			  "ctxt%u: max Eager buffer RcvArray entries: %u\n",
			  rcd->ctxt, rcd->egrbufs.count);

		/*
		 * Allocate array that will hold the eager buffer accounting
		 * data.
		 * This will allocate the maximum possible buffer count based
		 * on the value of the RcvArray split parameter.
		 * The resulting value will be rounded down to the closest
		 * multiple of dd->rcv_entries.group_size.
		 */
		rcd->egrbufs.buffers =
			kcalloc_node(rcd->egrbufs.count,
				     sizeof(*rcd->egrbufs.buffers),
				     GFP_KERNEL, numa);
		if (!rcd->egrbufs.buffers)
			goto bail;
		rcd->egrbufs.rcvtids =
			kcalloc_node(rcd->egrbufs.count,
				     sizeof(*rcd->egrbufs.rcvtids),
				     GFP_KERNEL, numa);
		if (!rcd->egrbufs.rcvtids)
			goto bail;
		rcd->egrbufs.size = eager_buffer_size;
		/*
		 * The size of the buffers programmed into the RcvArray
		 * entries needs to be big enough to handle the highest
		 * MTU supported.
		 */
		if (rcd->egrbufs.size < hfi1_max_mtu) {
			rcd->egrbufs.size = __roundup_pow_of_two(hfi1_max_mtu);
			hfi1_cdbg(PROC,
				  "ctxt%u: eager bufs size too small. Adjusting to %u\n",
				    rcd->ctxt, rcd->egrbufs.size);
		}
		rcd->egrbufs.rcvtid_size = HFI1_MAX_EAGER_BUFFER_SIZE;

		/* Applicable only for statically created kernel contexts */
		if (ctxt < dd->first_dyn_alloc_ctxt) {
			rcd->opstats = kzalloc_node(sizeof(*rcd->opstats),
						    GFP_KERNEL, numa);
			if (!rcd->opstats)
				goto bail;

			/* Initialize TID flow generations for the context */
			hfi1_kern_init_ctxt_generations(rcd);
		}

		*context = rcd;
		return 0;
	}

bail:
	*context = NULL;
	hfi1_free_ctxt(rcd);
	return -ENOMEM;
}