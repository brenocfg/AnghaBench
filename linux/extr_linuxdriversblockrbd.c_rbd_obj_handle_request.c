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
struct rbd_obj_request {struct rbd_img_request* img_request; } ;
struct rbd_img_request {struct rbd_obj_request* obj_request; int /*<<< orphan*/  flags; int /*<<< orphan*/  completion_lock; scalar_t__ pending_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_REQ_CHILD ; 
 int /*<<< orphan*/  __rbd_obj_handle_request (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_assert (scalar_t__) ; 
 int /*<<< orphan*/  rbd_img_end_child_request (struct rbd_img_request*) ; 
 int /*<<< orphan*/  rbd_img_end_request (struct rbd_img_request*) ; 
 int /*<<< orphan*/  rbd_obj_end_request (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_obj_handle_request(struct rbd_obj_request *obj_req)
{
	struct rbd_img_request *img_req;

again:
	if (!__rbd_obj_handle_request(obj_req))
		return;

	img_req = obj_req->img_request;
	spin_lock(&img_req->completion_lock);
	rbd_obj_end_request(obj_req);
	rbd_assert(img_req->pending_count);
	if (--img_req->pending_count) {
		spin_unlock(&img_req->completion_lock);
		return;
	}

	spin_unlock(&img_req->completion_lock);
	if (test_bit(IMG_REQ_CHILD, &img_req->flags)) {
		obj_req = img_req->obj_request;
		rbd_img_end_child_request(img_req);
		goto again;
	}
	rbd_img_end_request(img_req);
}