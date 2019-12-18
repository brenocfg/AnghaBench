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
struct whc_qset {int /*<<< orphan*/  remove; int /*<<< orphan*/  in_sw_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  usb_hcd; } ;
struct whc {int /*<<< orphan*/  async_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  lock; TYPE_1__ wusbhc; } ;
struct urb {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  asl_qset_insert_begin (struct whc*,struct whc_qset*) ; 
 struct whc_qset* get_qset (struct whc*,struct urb*,int /*<<< orphan*/ ) ; 
 int qset_add_urb (struct whc*,struct whc_qset*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_link_urb_to_ep (int /*<<< orphan*/ *,struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ *,struct urb*) ; 

int asl_urb_enqueue(struct whc *whc, struct urb *urb, gfp_t mem_flags)
{
	struct whc_qset *qset;
	int err;
	unsigned long flags;

	spin_lock_irqsave(&whc->lock, flags);

	err = usb_hcd_link_urb_to_ep(&whc->wusbhc.usb_hcd, urb);
	if (err < 0) {
		spin_unlock_irqrestore(&whc->lock, flags);
		return err;
	}

	qset = get_qset(whc, urb, GFP_ATOMIC);
	if (qset == NULL)
		err = -ENOMEM;
	else
		err = qset_add_urb(whc, qset, urb, GFP_ATOMIC);
	if (!err) {
		if (!qset->in_sw_list && !qset->remove)
			asl_qset_insert_begin(whc, qset);
	} else
		usb_hcd_unlink_urb_from_ep(&whc->wusbhc.usb_hcd, urb);

	spin_unlock_irqrestore(&whc->lock, flags);

	if (!err)
		queue_work(whc->workqueue, &whc->async_work);

	return err;
}