#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int /*<<< orphan*/  oe_len; int /*<<< orphan*/  oe_off; } ;
struct rbd_obj_request {TYPE_2__* osd_req; TYPE_1__ ex; scalar_t__ num_img_extents; } ;
struct TYPE_5__ {unsigned int r_num_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_CREATE ; 
 int /*<<< orphan*/  CEPH_OSD_OP_DELETE ; 
 scalar_t__ CEPH_OSD_OP_TRUNCATE ; 
 scalar_t__ CEPH_OSD_OP_ZERO ; 
 int /*<<< orphan*/  osd_req_op_extent_init (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_req_op_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 scalar_t__ rbd_obj_is_entire (struct rbd_obj_request*) ; 
 scalar_t__ rbd_obj_is_tail (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_osd_req_format_write (struct rbd_obj_request*) ; 

__attribute__((used)) static void __rbd_obj_setup_discard(struct rbd_obj_request *obj_req,
				    unsigned int which)
{
	u16 opcode;

	if (rbd_obj_is_entire(obj_req)) {
		if (obj_req->num_img_extents) {
			osd_req_op_init(obj_req->osd_req, which++,
					CEPH_OSD_OP_CREATE, 0);
			opcode = CEPH_OSD_OP_TRUNCATE;
		} else {
			osd_req_op_init(obj_req->osd_req, which++,
					CEPH_OSD_OP_DELETE, 0);
			opcode = 0;
		}
	} else if (rbd_obj_is_tail(obj_req)) {
		opcode = CEPH_OSD_OP_TRUNCATE;
	} else {
		opcode = CEPH_OSD_OP_ZERO;
	}

	if (opcode)
		osd_req_op_extent_init(obj_req->osd_req, which++, opcode,
				       obj_req->ex.oe_off, obj_req->ex.oe_len,
				       0, 0);

	rbd_assert(which == obj_req->osd_req->r_num_ops);
	rbd_osd_req_format_write(obj_req);
}