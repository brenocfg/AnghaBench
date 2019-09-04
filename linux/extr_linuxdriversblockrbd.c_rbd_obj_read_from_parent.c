#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rbd_obj_request {int /*<<< orphan*/  copyup_bvecs; int /*<<< orphan*/  num_img_extents; int /*<<< orphan*/  img_extents; int /*<<< orphan*/  bvec_pos; int /*<<< orphan*/  bio_pos; struct rbd_img_request* img_request; } ;
struct rbd_img_request {int data_type; struct rbd_obj_request* obj_request; int /*<<< orphan*/  flags; TYPE_1__* rbd_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IMG_REQ_CHILD ; 
 int /*<<< orphan*/  OBJ_OP_READ ; 
#define  OBJ_REQUEST_BIO 130 
#define  OBJ_REQUEST_BVECS 129 
#define  OBJ_REQUEST_OWN_BVECS 128 
 int __rbd_img_fill_from_bio (struct rbd_img_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __rbd_img_fill_from_bvecs (struct rbd_img_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 int rbd_img_fill_from_bvecs (struct rbd_img_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_img_is_write (struct rbd_img_request*) ; 
 struct rbd_img_request* rbd_img_request_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_img_request_put (struct rbd_img_request*) ; 
 int /*<<< orphan*/  rbd_img_request_submit (struct rbd_img_request*) ; 

__attribute__((used)) static int rbd_obj_read_from_parent(struct rbd_obj_request *obj_req)
{
	struct rbd_img_request *img_req = obj_req->img_request;
	struct rbd_img_request *child_img_req;
	int ret;

	child_img_req = rbd_img_request_create(img_req->rbd_dev->parent,
					       OBJ_OP_READ, NULL);
	if (!child_img_req)
		return -ENOMEM;

	__set_bit(IMG_REQ_CHILD, &child_img_req->flags);
	child_img_req->obj_request = obj_req;

	if (!rbd_img_is_write(img_req)) {
		switch (img_req->data_type) {
		case OBJ_REQUEST_BIO:
			ret = __rbd_img_fill_from_bio(child_img_req,
						      obj_req->img_extents,
						      obj_req->num_img_extents,
						      &obj_req->bio_pos);
			break;
		case OBJ_REQUEST_BVECS:
		case OBJ_REQUEST_OWN_BVECS:
			ret = __rbd_img_fill_from_bvecs(child_img_req,
						      obj_req->img_extents,
						      obj_req->num_img_extents,
						      &obj_req->bvec_pos);
			break;
		default:
			rbd_assert(0);
		}
	} else {
		ret = rbd_img_fill_from_bvecs(child_img_req,
					      obj_req->img_extents,
					      obj_req->num_img_extents,
					      obj_req->copyup_bvecs);
	}
	if (ret) {
		rbd_img_request_put(child_img_req);
		return ret;
	}

	rbd_img_request_submit(child_img_req);
	return 0;
}