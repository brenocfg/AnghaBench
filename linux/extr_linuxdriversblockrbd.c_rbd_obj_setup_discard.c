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
struct rbd_obj_request {scalar_t__ num_img_extents; int /*<<< orphan*/  osd_req; void* write_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* RBD_OBJ_WRITE_FLAT ; 
 void* RBD_OBJ_WRITE_GUARD ; 
 int /*<<< orphan*/  __rbd_obj_setup_discard (struct rbd_obj_request*,unsigned int) ; 
 int __rbd_obj_setup_stat (struct rbd_obj_request*,int /*<<< orphan*/ ) ; 
 int rbd_obj_calc_img_extents (struct rbd_obj_request*,int) ; 
 scalar_t__ rbd_obj_is_entire (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_osd_req_create (struct rbd_obj_request*,unsigned int) ; 

__attribute__((used)) static int rbd_obj_setup_discard(struct rbd_obj_request *obj_req)
{
	unsigned int num_osd_ops, which = 0;
	int ret;

	/* reverse map the entire object onto the parent */
	ret = rbd_obj_calc_img_extents(obj_req, true);
	if (ret)
		return ret;

	if (rbd_obj_is_entire(obj_req)) {
		obj_req->write_state = RBD_OBJ_WRITE_FLAT;
		if (obj_req->num_img_extents)
			num_osd_ops = 2; /* create + truncate */
		else
			num_osd_ops = 1; /* delete */
	} else {
		if (obj_req->num_img_extents) {
			obj_req->write_state = RBD_OBJ_WRITE_GUARD;
			num_osd_ops = 2; /* stat + truncate/zero */
		} else {
			obj_req->write_state = RBD_OBJ_WRITE_FLAT;
			num_osd_ops = 1; /* truncate/zero */
		}
	}

	obj_req->osd_req = rbd_osd_req_create(obj_req, num_osd_ops);
	if (!obj_req->osd_req)
		return -ENOMEM;

	if (!rbd_obj_is_entire(obj_req) && obj_req->num_img_extents) {
		ret = __rbd_obj_setup_stat(obj_req, which++);
		if (ret)
			return ret;
	}

	__rbd_obj_setup_discard(obj_req, which);
	return 0;
}