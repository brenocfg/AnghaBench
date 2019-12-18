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
typedef  scalar_t__ u32 ;
struct list_head {int dummy; } ;
struct mei_device {struct list_head ctrl_rd_list; } ;
struct mei_cl_cb {int /*<<< orphan*/  list; int /*<<< orphan*/  fop_type; } ;
struct mei_cl {int status; struct mei_device* dev; } ;
struct hbm_client_connect_request {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int mei_cl_notify_fop2req (int /*<<< orphan*/ ) ; 
 scalar_t__ mei_hbm2slots (int) ; 
 int mei_hbm_cl_notify_req (struct mei_device*,struct mei_cl*,int) ; 
 int mei_hbuf_empty_slots (struct mei_device*) ; 

int mei_cl_irq_notify(struct mei_cl *cl, struct mei_cl_cb *cb,
		      struct list_head *cmpl_list)
{
	struct mei_device *dev = cl->dev;
	u32 msg_slots;
	int slots;
	int ret;
	bool request;

	msg_slots = mei_hbm2slots(sizeof(struct hbm_client_connect_request));
	slots = mei_hbuf_empty_slots(dev);
	if (slots < 0)
		return -EOVERFLOW;

	if ((u32)slots < msg_slots)
		return -EMSGSIZE;

	request = mei_cl_notify_fop2req(cb->fop_type);
	ret = mei_hbm_cl_notify_req(dev, cl, request);
	if (ret) {
		cl->status = ret;
		list_move_tail(&cb->list, cmpl_list);
		return ret;
	}

	list_move_tail(&cb->list, &dev->ctrl_rd_list);
	return 0;
}