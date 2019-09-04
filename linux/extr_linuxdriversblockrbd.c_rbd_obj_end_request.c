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
struct TYPE_2__ {int /*<<< orphan*/  oe_len; int /*<<< orphan*/  oe_off; int /*<<< orphan*/  oe_objno; } ;
struct rbd_obj_request {int /*<<< orphan*/  result; int /*<<< orphan*/  xferred; TYPE_1__ ex; struct rbd_img_request* img_request; } ;
struct rbd_img_request {scalar_t__ xferred; int /*<<< orphan*/  result; int /*<<< orphan*/  op_type; int /*<<< orphan*/  rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  obj_op_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int /*<<< orphan*/  rbd_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbd_obj_end_request(struct rbd_obj_request *obj_req)
{
	struct rbd_img_request *img_req = obj_req->img_request;

	rbd_assert((!obj_req->result &&
		    obj_req->xferred == obj_req->ex.oe_len) ||
		   (obj_req->result < 0 && !obj_req->xferred));
	if (!obj_req->result) {
		img_req->xferred += obj_req->xferred;
		return;
	}

	rbd_warn(img_req->rbd_dev,
		 "%s at objno %llu %llu~%llu result %d xferred %llu",
		 obj_op_name(img_req->op_type), obj_req->ex.oe_objno,
		 obj_req->ex.oe_off, obj_req->ex.oe_len, obj_req->result,
		 obj_req->xferred);
	if (!img_req->result) {
		img_req->result = obj_req->result;
		img_req->xferred = 0;
	}
}