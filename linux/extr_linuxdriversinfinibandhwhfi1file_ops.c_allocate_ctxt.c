#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hfi1_user_info {int /*<<< orphan*/  uuid; int /*<<< orphan*/  userversion; scalar_t__ subctxt_cnt; } ;
struct hfi1_filedata {int rec_cpu_num; int /*<<< orphan*/  subctxt; } ;
struct hfi1_devdata {int flags; scalar_t__ num_user_contexts; int /*<<< orphan*/  freectxts; int /*<<< orphan*/  node; int /*<<< orphan*/  pport; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  jkey; int /*<<< orphan*/  uuid; int /*<<< orphan*/  comm; int /*<<< orphan*/  wait; int /*<<< orphan*/  flags; int /*<<< orphan*/  userversion; int /*<<< orphan*/  in_use_ctxts; TYPE_1__* sc; int /*<<< orphan*/  rcvhdrqentsize; int /*<<< orphan*/  numa_id; int /*<<< orphan*/  ctxt; } ;
struct TYPE_7__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {int /*<<< orphan*/  sps_ctxts; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_context; int /*<<< orphan*/  sw_index; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int HFI1_FROZEN ; 
 int /*<<< orphan*/  PROC ; 
 int /*<<< orphan*/  SC_USER ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspm_disable_all (struct hfi1_devdata*) ; 
 int cpu_to_node (int) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  generate_jkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_cap_mask ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int hfi1_create_ctxtdata (int /*<<< orphan*/ ,int,struct hfi1_ctxtdata**) ; 
 int /*<<< orphan*/  hfi1_free_ctxt (struct hfi1_ctxtdata*) ; 
 int hfi1_get_proc_affinity (int /*<<< orphan*/ ) ; 
 TYPE_3__ hfi1_stats ; 
 int /*<<< orphan*/  init_subctxts (struct hfi1_ctxtdata*,struct hfi1_user_info*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int numa_node_id () ; 
 TYPE_1__* sc_alloc (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sc_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int allocate_ctxt(struct hfi1_filedata *fd, struct hfi1_devdata *dd,
			 struct hfi1_user_info *uinfo,
			 struct hfi1_ctxtdata **rcd)
{
	struct hfi1_ctxtdata *uctxt;
	int ret, numa;

	if (dd->flags & HFI1_FROZEN) {
		/*
		 * Pick an error that is unique from all other errors
		 * that are returned so the user process knows that
		 * it tried to allocate while the SPC was frozen.  It
		 * it should be able to retry with success in a short
		 * while.
		 */
		return -EIO;
	}

	if (!dd->freectxts)
		return -EBUSY;

	/*
	 * If we don't have a NUMA node requested, preference is towards
	 * device NUMA node.
	 */
	fd->rec_cpu_num = hfi1_get_proc_affinity(dd->node);
	if (fd->rec_cpu_num != -1)
		numa = cpu_to_node(fd->rec_cpu_num);
	else
		numa = numa_node_id();
	ret = hfi1_create_ctxtdata(dd->pport, numa, &uctxt);
	if (ret < 0) {
		dd_dev_err(dd, "user ctxtdata allocation failed\n");
		return ret;
	}
	hfi1_cdbg(PROC, "[%u:%u] pid %u assigned to CPU %d (NUMA %u)",
		  uctxt->ctxt, fd->subctxt, current->pid, fd->rec_cpu_num,
		  uctxt->numa_id);

	/*
	 * Allocate and enable a PIO send context.
	 */
	uctxt->sc = sc_alloc(dd, SC_USER, uctxt->rcvhdrqentsize, dd->node);
	if (!uctxt->sc) {
		ret = -ENOMEM;
		goto ctxdata_free;
	}
	hfi1_cdbg(PROC, "allocated send context %u(%u)\n", uctxt->sc->sw_index,
		  uctxt->sc->hw_context);
	ret = sc_enable(uctxt->sc);
	if (ret)
		goto ctxdata_free;

	/*
	 * Setup sub context information if the user-level has requested
	 * sub contexts.
	 * This has to be done here so the rest of the sub-contexts find the
	 * proper base context.
	 * NOTE: _set_bit() can be used here because the context creation is
	 * protected by the mutex (rather than the spin_lock), and will be the
	 * very first instance of this context.
	 */
	__set_bit(0, uctxt->in_use_ctxts);
	if (uinfo->subctxt_cnt)
		init_subctxts(uctxt, uinfo);
	uctxt->userversion = uinfo->userversion;
	uctxt->flags = hfi1_cap_mask; /* save current flag state */
	init_waitqueue_head(&uctxt->wait);
	strlcpy(uctxt->comm, current->comm, sizeof(uctxt->comm));
	memcpy(uctxt->uuid, uinfo->uuid, sizeof(uctxt->uuid));
	uctxt->jkey = generate_jkey(current_uid());
	hfi1_stats.sps_ctxts++;
	/*
	 * Disable ASPM when there are open user/PSM contexts to avoid
	 * issues with ASPM L1 exit latency
	 */
	if (dd->freectxts-- == dd->num_user_contexts)
		aspm_disable_all(dd);

	*rcd = uctxt;

	return 0;

ctxdata_free:
	hfi1_free_ctxt(uctxt);
	return ret;
}