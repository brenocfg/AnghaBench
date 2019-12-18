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
struct tb_ctl {int /*<<< orphan*/  request_queue_lock; } ;
struct tb_cfg_request {int /*<<< orphan*/  flags; int /*<<< orphan*/  list; struct tb_ctl* ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_REQUEST_ACTIVE ; 
 int /*<<< orphan*/  TB_CFG_REQUEST_CANCELED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_cfg_request_cancel_queue ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tb_cfg_request_dequeue(struct tb_cfg_request *req)
{
	struct tb_ctl *ctl = req->ctl;

	mutex_lock(&ctl->request_queue_lock);
	list_del(&req->list);
	clear_bit(TB_CFG_REQUEST_ACTIVE, &req->flags);
	if (test_bit(TB_CFG_REQUEST_CANCELED, &req->flags))
		wake_up(&tb_cfg_request_cancel_queue);
	mutex_unlock(&ctl->request_queue_lock);
}