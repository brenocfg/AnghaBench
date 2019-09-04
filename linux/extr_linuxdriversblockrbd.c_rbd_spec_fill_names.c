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
struct rbd_spec {scalar_t__ pool_id; int image_id; scalar_t__ snap_id; char const* pool_name; char const* image_name; char const* snap_name; } ;
struct rbd_device {struct rbd_spec* spec; TYPE_2__* rbd_client; } ;
struct ceph_osd_client {int /*<<< orphan*/  osdmap; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOPOOL ; 
 scalar_t__ CEPH_NOSNAP ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 char* ceph_pg_pool_name_by_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 char* rbd_dev_image_name (struct rbd_device*) ; 
 char* rbd_snap_name (struct rbd_device*,scalar_t__) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,...) ; 

__attribute__((used)) static int rbd_spec_fill_names(struct rbd_device *rbd_dev)
{
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	struct rbd_spec *spec = rbd_dev->spec;
	const char *pool_name;
	const char *image_name;
	const char *snap_name;
	int ret;

	rbd_assert(spec->pool_id != CEPH_NOPOOL);
	rbd_assert(spec->image_id);
	rbd_assert(spec->snap_id != CEPH_NOSNAP);

	/* Get the pool name; we have to make our own copy of this */

	pool_name = ceph_pg_pool_name_by_id(osdc->osdmap, spec->pool_id);
	if (!pool_name) {
		rbd_warn(rbd_dev, "no pool with id %llu", spec->pool_id);
		return -EIO;
	}
	pool_name = kstrdup(pool_name, GFP_KERNEL);
	if (!pool_name)
		return -ENOMEM;

	/* Fetch the image name; tolerate failure here */

	image_name = rbd_dev_image_name(rbd_dev);
	if (!image_name)
		rbd_warn(rbd_dev, "unable to get image name");

	/* Fetch the snapshot name */

	snap_name = rbd_snap_name(rbd_dev, spec->snap_id);
	if (IS_ERR(snap_name)) {
		ret = PTR_ERR(snap_name);
		goto out_err;
	}

	spec->pool_name = pool_name;
	spec->image_name = image_name;
	spec->snap_name = snap_name;

	return 0;

out_err:
	kfree(image_name);
	kfree(pool_name);
	return ret;
}