#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int /*<<< orphan*/  oe_len; int /*<<< orphan*/  oe_off; } ;
struct rbd_obj_request {TYPE_4__* osd_req; TYPE_2__ ex; TYPE_3__* img_request; } ;
struct TYPE_6__ {int /*<<< orphan*/  object_size; } ;
struct rbd_device {TYPE_1__ layout; } ;
struct TYPE_9__ {unsigned int r_num_ops; } ;
struct TYPE_8__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_WRITE ; 
 int /*<<< orphan*/  CEPH_OSD_OP_WRITEFULL ; 
 int /*<<< orphan*/  osd_req_op_alloc_hint_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_req_op_extent_init (TYPE_4__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 scalar_t__ rbd_obj_is_entire (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_osd_req_format_write (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_osd_req_setup_data (struct rbd_obj_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rbd_obj_setup_write(struct rbd_obj_request *obj_req,
				  unsigned int which)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	u16 opcode;

	osd_req_op_alloc_hint_init(obj_req->osd_req, which++,
				   rbd_dev->layout.object_size,
				   rbd_dev->layout.object_size);

	if (rbd_obj_is_entire(obj_req))
		opcode = CEPH_OSD_OP_WRITEFULL;
	else
		opcode = CEPH_OSD_OP_WRITE;

	osd_req_op_extent_init(obj_req->osd_req, which, opcode,
			       obj_req->ex.oe_off, obj_req->ex.oe_len, 0, 0);
	rbd_osd_req_setup_data(obj_req, which++);

	rbd_assert(which == obj_req->osd_req->r_num_ops);
	rbd_osd_req_format_write(obj_req);
}