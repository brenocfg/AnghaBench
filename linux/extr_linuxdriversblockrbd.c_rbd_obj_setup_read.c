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
struct TYPE_2__ {int /*<<< orphan*/  oe_len; int /*<<< orphan*/  oe_off; } ;
struct rbd_obj_request {TYPE_1__ ex; int /*<<< orphan*/  osd_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_READ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  osd_req_op_extent_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_osd_req_create (struct rbd_obj_request*,int) ; 
 int /*<<< orphan*/  rbd_osd_req_format_read (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_osd_req_setup_data (struct rbd_obj_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbd_obj_setup_read(struct rbd_obj_request *obj_req)
{
	obj_req->osd_req = rbd_osd_req_create(obj_req, 1);
	if (!obj_req->osd_req)
		return -ENOMEM;

	osd_req_op_extent_init(obj_req->osd_req, 0, CEPH_OSD_OP_READ,
			       obj_req->ex.oe_off, obj_req->ex.oe_len, 0, 0);
	rbd_osd_req_setup_data(obj_req, 0);

	rbd_osd_req_format_read(obj_req);
	return 0;
}