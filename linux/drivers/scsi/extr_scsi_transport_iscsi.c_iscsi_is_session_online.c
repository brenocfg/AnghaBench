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
struct iscsi_cls_session {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ ISCSI_SESSION_LOGGED_IN ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int iscsi_is_session_online(struct iscsi_cls_session *session)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&session->lock, flags);
	if (session->state == ISCSI_SESSION_LOGGED_IN)
		ret = 1;
	spin_unlock_irqrestore(&session->lock, flags);
	return ret;
}