#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hfi1_filedata {struct hfi1_ctxtdata* uctxt; } ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  wait; int /*<<< orphan*/  event_flags; scalar_t__ subctxt_cnt; int /*<<< orphan*/  sc; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_CTXT_BASE_FAILED ; 
 int /*<<< orphan*/  HFI1_CTXT_BASE_UNINIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hfi1_alloc_ctxt_rcv_groups (struct hfi1_ctxtdata*) ; 
 int hfi1_create_rcvhdrq (struct hfi1_devdata*,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_init_ctxt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_rcd_get (struct hfi1_ctxtdata*) ; 
 int hfi1_setup_eagerbufs (struct hfi1_ctxtdata*) ; 
 int init_user_ctxt (struct hfi1_filedata*,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int setup_subctxt (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  user_init (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_base_ctxt(struct hfi1_filedata *fd,
			   struct hfi1_ctxtdata *uctxt)
{
	struct hfi1_devdata *dd = uctxt->dd;
	int ret = 0;

	hfi1_init_ctxt(uctxt->sc);

	/* Now allocate the RcvHdr queue and eager buffers. */
	ret = hfi1_create_rcvhdrq(dd, uctxt);
	if (ret)
		goto done;

	ret = hfi1_setup_eagerbufs(uctxt);
	if (ret)
		goto done;

	/* If sub-contexts are enabled, do the appropriate setup */
	if (uctxt->subctxt_cnt)
		ret = setup_subctxt(uctxt);
	if (ret)
		goto done;

	ret = hfi1_alloc_ctxt_rcv_groups(uctxt);
	if (ret)
		goto done;

	ret = init_user_ctxt(fd, uctxt);
	if (ret)
		goto done;

	user_init(uctxt);

	/* Now that the context is set up, the fd can get a reference. */
	fd->uctxt = uctxt;
	hfi1_rcd_get(uctxt);

done:
	if (uctxt->subctxt_cnt) {
		/*
		 * On error, set the failed bit so sub-contexts will clean up
		 * correctly.
		 */
		if (ret)
			set_bit(HFI1_CTXT_BASE_FAILED, &uctxt->event_flags);

		/*
		 * Base context is done (successfully or not), notify anybody
		 * using a sub-context that is waiting for this completion.
		 */
		clear_bit(HFI1_CTXT_BASE_UNINIT, &uctxt->event_flags);
		wake_up(&uctxt->wait);
	}

	return ret;
}