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
struct media_request_object_ops {int /*<<< orphan*/  release; } ;
struct media_request_object {int /*<<< orphan*/  list; void* priv; struct media_request_object_ops const* ops; struct media_request* req; } ;
struct media_request {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_incomplete_objects; int /*<<< orphan*/  objects; } ;

/* Variables and functions */
 int EBADR ; 
 int EBUSY ; 
 scalar_t__ MEDIA_REQUEST_STATE_UPDATING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int media_request_object_bind(struct media_request *req,
			      const struct media_request_object_ops *ops,
			      void *priv, bool is_buffer,
			      struct media_request_object *obj)
{
	unsigned long flags;
	int ret = -EBUSY;

	if (WARN_ON(!ops->release))
		return -EBADR;

	spin_lock_irqsave(&req->lock, flags);

	if (WARN_ON(req->state != MEDIA_REQUEST_STATE_UPDATING))
		goto unlock;

	obj->req = req;
	obj->ops = ops;
	obj->priv = priv;

	if (is_buffer)
		list_add_tail(&obj->list, &req->objects);
	else
		list_add(&obj->list, &req->objects);
	req->num_incomplete_objects++;
	ret = 0;

unlock:
	spin_unlock_irqrestore(&req->lock, flags);
	return ret;
}