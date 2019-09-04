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
struct TYPE_2__ {int oe_len; } ;
struct rbd_obj_request {int write_state; int xferred; int result; TYPE_1__ ex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOENT ; 
#define  RBD_OBJ_WRITE_COPYUP 130 
#define  RBD_OBJ_WRITE_FLAT 129 
#define  RBD_OBJ_WRITE_GUARD 128 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_obj_handle_write_guard (struct rbd_obj_request*) ; 
 int rbd_obj_issue_copyup (struct rbd_obj_request*,int) ; 

__attribute__((used)) static bool rbd_obj_handle_write(struct rbd_obj_request *obj_req)
{
	int ret;

again:
	switch (obj_req->write_state) {
	case RBD_OBJ_WRITE_GUARD:
		rbd_assert(!obj_req->xferred);
		if (obj_req->result == -ENOENT) {
			/*
			 * The target object doesn't exist.  Read the data for
			 * the entire target object up to the overlap point (if
			 * any) from the parent, so we can use it for a copyup.
			 */
			ret = rbd_obj_handle_write_guard(obj_req);
			if (ret) {
				obj_req->result = ret;
				return true;
			}
			return false;
		}
		/* fall through */
	case RBD_OBJ_WRITE_FLAT:
		if (!obj_req->result)
			/*
			 * There is no such thing as a successful short
			 * write -- indicate the whole request was satisfied.
			 */
			obj_req->xferred = obj_req->ex.oe_len;
		return true;
	case RBD_OBJ_WRITE_COPYUP:
		obj_req->write_state = RBD_OBJ_WRITE_GUARD;
		if (obj_req->result)
			goto again;

		rbd_assert(obj_req->xferred);
		ret = rbd_obj_issue_copyup(obj_req, obj_req->xferred);
		if (ret) {
			obj_req->result = ret;
			return true;
		}
		return false;
	default:
		BUG();
	}
}