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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  comp_handler; } ;
struct siw_cq {TYPE_2__* notify; TYPE_1__ base_cq; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int SIW_NOTIFY_NEXT_COMPLETION ; 
 int /*<<< orphan*/  SIW_NOTIFY_NOT ; 
 int SIW_NOTIFY_SOLICITED ; 
 int SIW_WQE_SOLICITED ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool siw_cq_notify_now(struct siw_cq *cq, u32 flags)
{
	u32 cq_notify;

	if (!cq->base_cq.comp_handler)
		return false;

	/* Read application shared notification state */
	cq_notify = READ_ONCE(cq->notify->flags);

	if ((cq_notify & SIW_NOTIFY_NEXT_COMPLETION) ||
	    ((cq_notify & SIW_NOTIFY_SOLICITED) &&
	     (flags & SIW_WQE_SOLICITED))) {
		/*
		 * CQ notification is one-shot: Since the
		 * current CQE causes user notification,
		 * the CQ gets dis-aremd and must be re-aremd
		 * by the user for a new notification.
		 */
		WRITE_ONCE(cq->notify->flags, SIW_NOTIFY_NOT);

		return true;
	}
	return false;
}