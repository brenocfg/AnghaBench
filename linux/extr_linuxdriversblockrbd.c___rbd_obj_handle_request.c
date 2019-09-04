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
struct TYPE_4__ {int /*<<< orphan*/  oe_len; } ;
struct rbd_obj_request {TYPE_2__ ex; int /*<<< orphan*/  xferred; int /*<<< orphan*/  result; TYPE_1__* img_request; } ;
struct TYPE_3__ {int op_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ENOENT ; 
#define  OBJ_OP_DISCARD 130 
#define  OBJ_OP_READ 129 
#define  OBJ_OP_WRITE 128 
 int rbd_obj_handle_read (struct rbd_obj_request*) ; 
 int rbd_obj_handle_write (struct rbd_obj_request*) ; 

__attribute__((used)) static bool __rbd_obj_handle_request(struct rbd_obj_request *obj_req)
{
	switch (obj_req->img_request->op_type) {
	case OBJ_OP_READ:
		return rbd_obj_handle_read(obj_req);
	case OBJ_OP_WRITE:
		return rbd_obj_handle_write(obj_req);
	case OBJ_OP_DISCARD:
		if (rbd_obj_handle_write(obj_req)) {
			/*
			 * Hide -ENOENT from delete/truncate/zero -- discarding
			 * a non-existent object is not a problem.
			 */
			if (obj_req->result == -ENOENT) {
				obj_req->result = 0;
				obj_req->xferred = obj_req->ex.oe_len;
			}
			return true;
		}
		return false;
	default:
		BUG();
	}
}