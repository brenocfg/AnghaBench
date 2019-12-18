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
struct tcs_request {int dummy; } ;
struct tcs_group {int /*<<< orphan*/  lock; } ;
struct rsc_drv {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tcs_group*) ; 
 int PTR_ERR (struct tcs_group*) ; 
 int /*<<< orphan*/  __tcs_buffer_write (struct rsc_drv*,int,int,struct tcs_request const*) ; 
 int find_slots (struct tcs_group*,struct tcs_request const*,int*,int*) ; 
 struct tcs_group* get_tcs_for_msg (struct rsc_drv*,struct tcs_request const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tcs_ctrl_write(struct rsc_drv *drv, const struct tcs_request *msg)
{
	struct tcs_group *tcs;
	int tcs_id = 0, cmd_id = 0;
	unsigned long flags;
	int ret;

	tcs = get_tcs_for_msg(drv, msg);
	if (IS_ERR(tcs))
		return PTR_ERR(tcs);

	spin_lock_irqsave(&tcs->lock, flags);
	/* find the TCS id and the command in the TCS to write to */
	ret = find_slots(tcs, msg, &tcs_id, &cmd_id);
	if (!ret)
		__tcs_buffer_write(drv, tcs_id, cmd_id, msg);
	spin_unlock_irqrestore(&tcs->lock, flags);

	return ret;
}