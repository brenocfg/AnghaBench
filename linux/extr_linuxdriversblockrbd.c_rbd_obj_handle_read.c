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
struct TYPE_4__ {scalar_t__ oe_len; } ;
struct rbd_obj_request {int result; int tried_parent; scalar_t__ xferred; TYPE_2__ ex; scalar_t__ num_img_extents; TYPE_1__* img_request; } ;
struct rbd_device {scalar_t__ parent_overlap; } ;
struct TYPE_3__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_obj_calc_img_extents (struct rbd_obj_request*,int) ; 
 int rbd_obj_read_from_parent (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_obj_zero_range (struct rbd_obj_request*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool rbd_obj_handle_read(struct rbd_obj_request *obj_req)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	int ret;

	if (obj_req->result == -ENOENT &&
	    rbd_dev->parent_overlap && !obj_req->tried_parent) {
		/* reverse map this object extent onto the parent */
		ret = rbd_obj_calc_img_extents(obj_req, false);
		if (ret) {
			obj_req->result = ret;
			return true;
		}

		if (obj_req->num_img_extents) {
			obj_req->tried_parent = true;
			ret = rbd_obj_read_from_parent(obj_req);
			if (ret) {
				obj_req->result = ret;
				return true;
			}
			return false;
		}
	}

	/*
	 * -ENOENT means a hole in the image -- zero-fill the entire
	 * length of the request.  A short read also implies zero-fill
	 * to the end of the request.  In both cases we update xferred
	 * count to indicate the whole request was satisfied.
	 */
	if (obj_req->result == -ENOENT ||
	    (!obj_req->result && obj_req->xferred < obj_req->ex.oe_len)) {
		rbd_assert(!obj_req->xferred || !obj_req->result);
		rbd_obj_zero_range(obj_req, obj_req->xferred,
				   obj_req->ex.oe_len - obj_req->xferred);
		obj_req->result = 0;
		obj_req->xferred = obj_req->ex.oe_len;
	}

	return true;
}