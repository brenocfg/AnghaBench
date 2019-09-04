#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct hfi1_user_info {scalar_t__ subctxt_id; scalar_t__ subctxt_cnt; scalar_t__ userversion; int /*<<< orphan*/  uuid; } ;
struct hfi1_filedata {struct hfi1_ctxtdata* uctxt; scalar_t__ subctxt; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int /*<<< orphan*/  uctxt_lock; } ;
struct hfi1_ctxtdata {scalar_t__ jkey; scalar_t__ subctxt_id; scalar_t__ subctxt_cnt; scalar_t__ userversion; int /*<<< orphan*/  in_use_ctxts; int /*<<< orphan*/  uuid; TYPE_1__* sc; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  HFI1_MAX_SHARED_CTXTS ; 
 scalar_t__ SC_KERNEL ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_uid () ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ generate_jkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_rcd_get (struct hfi1_ctxtdata*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int match_ctxt(struct hfi1_filedata *fd,
		      const struct hfi1_user_info *uinfo,
		      struct hfi1_ctxtdata *uctxt)
{
	struct hfi1_devdata *dd = fd->dd;
	unsigned long flags;
	u16 subctxt;

	/* Skip dynamically allocated kernel contexts */
	if (uctxt->sc && (uctxt->sc->type == SC_KERNEL))
		return 0;

	/* Skip ctxt if it doesn't match the requested one */
	if (memcmp(uctxt->uuid, uinfo->uuid, sizeof(uctxt->uuid)) ||
	    uctxt->jkey != generate_jkey(current_uid()) ||
	    uctxt->subctxt_id != uinfo->subctxt_id ||
	    uctxt->subctxt_cnt != uinfo->subctxt_cnt)
		return 0;

	/* Verify the sharing process matches the base */
	if (uctxt->userversion != uinfo->userversion)
		return -EINVAL;

	/* Find an unused sub context */
	spin_lock_irqsave(&dd->uctxt_lock, flags);
	if (bitmap_empty(uctxt->in_use_ctxts, HFI1_MAX_SHARED_CTXTS)) {
		/* context is being closed, do not use */
		spin_unlock_irqrestore(&dd->uctxt_lock, flags);
		return 0;
	}

	subctxt = find_first_zero_bit(uctxt->in_use_ctxts,
				      HFI1_MAX_SHARED_CTXTS);
	if (subctxt >= uctxt->subctxt_cnt) {
		spin_unlock_irqrestore(&dd->uctxt_lock, flags);
		return -EBUSY;
	}

	fd->subctxt = subctxt;
	__set_bit(fd->subctxt, uctxt->in_use_ctxts);
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	fd->uctxt = uctxt;
	hfi1_rcd_get(uctxt);

	return 1;
}