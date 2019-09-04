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
struct rbd_obj_request {TYPE_1__* img_request; struct ceph_osd_request* osd_req; } ;
struct ceph_osd_request {int /*<<< orphan*/  r_snapid; int /*<<< orphan*/  r_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  snap_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_FLAG_READ ; 

__attribute__((used)) static void rbd_osd_req_format_read(struct rbd_obj_request *obj_request)
{
	struct ceph_osd_request *osd_req = obj_request->osd_req;

	osd_req->r_flags = CEPH_OSD_FLAG_READ;
	osd_req->r_snapid = obj_request->img_request->snap_id;
}