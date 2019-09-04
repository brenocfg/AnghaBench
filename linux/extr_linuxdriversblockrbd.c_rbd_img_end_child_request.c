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
struct rbd_obj_request {scalar_t__ result; scalar_t__ xferred; } ;
struct rbd_img_request {scalar_t__ result; scalar_t__ xferred; int /*<<< orphan*/  flags; struct rbd_obj_request* obj_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_REQ_CHILD ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int /*<<< orphan*/  rbd_img_request_put (struct rbd_img_request*) ; 
 scalar_t__ rbd_obj_img_extents_bytes (struct rbd_obj_request*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_img_end_child_request(struct rbd_img_request *img_req)
{
	struct rbd_obj_request *obj_req = img_req->obj_request;

	rbd_assert(test_bit(IMG_REQ_CHILD, &img_req->flags));
	rbd_assert((!img_req->result &&
		    img_req->xferred == rbd_obj_img_extents_bytes(obj_req)) ||
		   (img_req->result < 0 && !img_req->xferred));

	obj_req->result = img_req->result;
	obj_req->xferred = img_req->xferred;
	rbd_img_request_put(img_req);
}