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
struct mei_device {int dummy; } ;
struct mei_cl_cb {int /*<<< orphan*/  list; } ;
struct mei_cl {struct mei_device* dev; } ;
struct list_head {int dummy; } ;
struct hbm_client_connect_request {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int mei_cl_send_disconnect (struct mei_cl*,struct mei_cl_cb*) ; 
 scalar_t__ mei_hbm2slots (int) ; 
 int mei_hbuf_empty_slots (struct mei_device*) ; 

int mei_cl_irq_disconnect(struct mei_cl *cl, struct mei_cl_cb *cb,
			  struct list_head *cmpl_list)
{
	struct mei_device *dev = cl->dev;
	u32 msg_slots;
	int slots;
	int ret;

	msg_slots = mei_hbm2slots(sizeof(struct hbm_client_connect_request));
	slots = mei_hbuf_empty_slots(dev);
	if (slots < 0)
		return -EOVERFLOW;

	if ((u32)slots < msg_slots)
		return -EMSGSIZE;

	ret = mei_cl_send_disconnect(cl, cb);
	if (ret)
		list_move_tail(&cb->list, cmpl_list);

	return ret;
}