#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  oe_objno; } ;
struct rbd_obj_request {TYPE_5__ ex; struct rbd_img_request* img_request; } ;
struct rbd_img_request {int /*<<< orphan*/ * snapc; struct rbd_device* rbd_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  object_prefix; } ;
struct TYPE_9__ {int /*<<< orphan*/  pool_id; } ;
struct rbd_device {int image_format; TYPE_4__ header; TYPE_3__ layout; int /*<<< orphan*/  header_oloc; TYPE_2__* rbd_client; } ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
struct ceph_osd_request {int /*<<< orphan*/  r_base_oid; TYPE_6__ r_base_oloc; struct rbd_obj_request* r_priv; int /*<<< orphan*/  r_callback; } ;
struct ceph_osd_client {int dummy; } ;
struct TYPE_8__ {TYPE_1__* client; } ;
struct TYPE_7__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 char* RBD_V1_DATA_FORMAT ; 
 char* RBD_V2_DATA_FORMAT ; 
 scalar_t__ ceph_oid_aprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_oloc_copy (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 struct ceph_osd_request* ceph_osdc_alloc_request (struct ceph_osd_client*,int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 scalar_t__ rbd_img_is_write (struct rbd_img_request*) ; 
 int /*<<< orphan*/  rbd_osd_req_callback ; 

__attribute__((used)) static struct ceph_osd_request *
rbd_osd_req_create(struct rbd_obj_request *obj_req, unsigned int num_ops)
{
	struct rbd_img_request *img_req = obj_req->img_request;
	struct rbd_device *rbd_dev = img_req->rbd_dev;
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	struct ceph_osd_request *req;
	const char *name_format = rbd_dev->image_format == 1 ?
				      RBD_V1_DATA_FORMAT : RBD_V2_DATA_FORMAT;

	req = ceph_osdc_alloc_request(osdc,
			(rbd_img_is_write(img_req) ? img_req->snapc : NULL),
			num_ops, false, GFP_NOIO);
	if (!req)
		return NULL;

	req->r_callback = rbd_osd_req_callback;
	req->r_priv = obj_req;

	/*
	 * Data objects may be stored in a separate pool, but always in
	 * the same namespace in that pool as the header in its pool.
	 */
	ceph_oloc_copy(&req->r_base_oloc, &rbd_dev->header_oloc);
	req->r_base_oloc.pool = rbd_dev->layout.pool_id;

	if (ceph_oid_aprintf(&req->r_base_oid, GFP_NOIO, name_format,
			rbd_dev->header.object_prefix, obj_req->ex.oe_objno))
		goto err_req;

	if (ceph_osdc_alloc_messages(req, GFP_NOIO))
		goto err_req;

	return req;

err_req:
	ceph_osdc_put_request(req);
	return NULL;
}