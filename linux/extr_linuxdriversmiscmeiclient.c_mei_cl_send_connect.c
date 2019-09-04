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
struct mei_device {int /*<<< orphan*/  ctrl_rd_list; } ;
struct mei_cl_cb {int /*<<< orphan*/  list; } ;
struct mei_cl {int status; int /*<<< orphan*/  timer_count; int /*<<< orphan*/  state; struct mei_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_CONNECT_TIMEOUT ; 
 int /*<<< orphan*/  MEI_FILE_DISCONNECT_REPLY ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mei_hbm_cl_connect_req (struct mei_device*,struct mei_cl*) ; 
 int /*<<< orphan*/  mei_schedule_stall_timer (struct mei_device*) ; 

__attribute__((used)) static int mei_cl_send_connect(struct mei_cl *cl, struct mei_cl_cb *cb)
{
	struct mei_device *dev;
	int ret;

	dev = cl->dev;

	ret = mei_hbm_cl_connect_req(dev, cl);
	cl->status = ret;
	if (ret) {
		cl->state = MEI_FILE_DISCONNECT_REPLY;
		return ret;
	}

	list_move_tail(&cb->list, &dev->ctrl_rd_list);
	cl->timer_count = MEI_CONNECT_TIMEOUT;
	mei_schedule_stall_timer(dev);
	return 0;
}