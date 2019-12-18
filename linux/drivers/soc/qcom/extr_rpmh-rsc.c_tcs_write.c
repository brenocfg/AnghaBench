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
struct tcs_group {int offset; int /*<<< orphan*/  lock; struct tcs_request const** req; } ;
struct rsc_drv {int /*<<< orphan*/  lock; int /*<<< orphan*/  tcs_in_use; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tcs_group*) ; 
 int PTR_ERR (struct tcs_group*) ; 
 int /*<<< orphan*/  __tcs_buffer_write (struct rsc_drv*,int,int /*<<< orphan*/ ,struct tcs_request const*) ; 
 int /*<<< orphan*/  __tcs_trigger (struct rsc_drv*,int) ; 
 int check_for_req_inflight (struct rsc_drv*,struct tcs_group*,struct tcs_request const*) ; 
 int find_free_tcs (struct tcs_group*) ; 
 struct tcs_group* get_tcs_for_msg (struct rsc_drv*,struct tcs_request const*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tcs_write(struct rsc_drv *drv, const struct tcs_request *msg)
{
	struct tcs_group *tcs;
	int tcs_id;
	unsigned long flags;
	int ret;

	tcs = get_tcs_for_msg(drv, msg);
	if (IS_ERR(tcs))
		return PTR_ERR(tcs);

	spin_lock_irqsave(&tcs->lock, flags);
	spin_lock(&drv->lock);
	/*
	 * The h/w does not like if we send a request to the same address,
	 * when one is already in-flight or being processed.
	 */
	ret = check_for_req_inflight(drv, tcs, msg);
	if (ret) {
		spin_unlock(&drv->lock);
		goto done_write;
	}

	tcs_id = find_free_tcs(tcs);
	if (tcs_id < 0) {
		ret = tcs_id;
		spin_unlock(&drv->lock);
		goto done_write;
	}

	tcs->req[tcs_id - tcs->offset] = msg;
	set_bit(tcs_id, drv->tcs_in_use);
	spin_unlock(&drv->lock);

	__tcs_buffer_write(drv, tcs_id, 0, msg);
	__tcs_trigger(drv, tcs_id);

done_write:
	spin_unlock_irqrestore(&tcs->lock, flags);
	return ret;
}