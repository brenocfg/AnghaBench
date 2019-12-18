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
typedef  void* u32 ;
struct rndis_set_request {int /*<<< orphan*/  req_id; } ;
struct TYPE_3__ {scalar_t__ q_idx; } ;
struct TYPE_4__ {struct rndis_set_request set_req; } ;
struct rndis_message {TYPE_2__ msg; void* msg_len; void* ndis_msg_type; } ;
struct rndis_request {int /*<<< orphan*/  list_ent; TYPE_1__ pkt; struct rndis_message request_msg; int /*<<< orphan*/  wait_event; } ;
struct rndis_device {int /*<<< orphan*/  request_lock; int /*<<< orphan*/  req_list; int /*<<< orphan*/  new_req_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct rndis_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct rndis_request *get_rndis_request(struct rndis_device *dev,
					     u32 msg_type,
					     u32 msg_len)
{
	struct rndis_request *request;
	struct rndis_message *rndis_msg;
	struct rndis_set_request *set;
	unsigned long flags;

	request = kzalloc(sizeof(struct rndis_request), GFP_KERNEL);
	if (!request)
		return NULL;

	init_completion(&request->wait_event);

	rndis_msg = &request->request_msg;
	rndis_msg->ndis_msg_type = msg_type;
	rndis_msg->msg_len = msg_len;

	request->pkt.q_idx = 0;

	/*
	 * Set the request id. This field is always after the rndis header for
	 * request/response packet types so we just used the SetRequest as a
	 * template
	 */
	set = &rndis_msg->msg.set_req;
	set->req_id = atomic_inc_return(&dev->new_req_id);

	/* Add to the request list */
	spin_lock_irqsave(&dev->request_lock, flags);
	list_add_tail(&request->list_ent, &dev->req_list);
	spin_unlock_irqrestore(&dev->request_lock, flags);

	return request;
}