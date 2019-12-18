#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fwnode; int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; } ;
struct TYPE_7__ {int link_subtype; } ;
struct coresight_device {scalar_t__ type; int orphan; TYPE_2__ dev; int /*<<< orphan*/  ops; TYPE_1__ subtype; TYPE_6__* pdata; int /*<<< orphan*/ * refcnt; } ;
struct coresight_desc {scalar_t__ type; TYPE_6__* pdata; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  groups; int /*<<< orphan*/  ops; TYPE_1__ subtype; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_9__ {int nr_inport; int nr_outport; } ;

/* Variables and functions */
 int CORESIGHT_DEV_SUBTYPE_LINK_MERG ; 
 int CORESIGHT_DEV_SUBTYPE_LINK_SPLIT ; 
 scalar_t__ CORESIGHT_DEV_TYPE_LINK ; 
 scalar_t__ CORESIGHT_DEV_TYPE_LINKSINK ; 
 scalar_t__ CORESIGHT_DEV_TYPE_SINK ; 
 int ENOMEM ; 
 struct coresight_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  coresight_bustype ; 
 int /*<<< orphan*/ * coresight_dev_type ; 
 int /*<<< orphan*/  coresight_device_release ; 
 int /*<<< orphan*/  coresight_fixup_device_conns (struct coresight_device*) ; 
 int /*<<< orphan*/  coresight_fixup_orphan_conns (struct coresight_device*) ; 
 int /*<<< orphan*/  coresight_mutex ; 
 int /*<<< orphan*/  coresight_release_platform_data (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int etm_perf_add_symlink_sink (struct coresight_device*) ; 
 int /*<<< orphan*/  fwnode_handle_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct coresight_device*) ; 
 struct coresight_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 

struct coresight_device *coresight_register(struct coresight_desc *desc)
{
	int ret;
	int link_subtype;
	int nr_refcnts = 1;
	atomic_t *refcnts = NULL;
	struct coresight_device *csdev;

	csdev = kzalloc(sizeof(*csdev), GFP_KERNEL);
	if (!csdev) {
		ret = -ENOMEM;
		goto err_out;
	}

	if (desc->type == CORESIGHT_DEV_TYPE_LINK ||
	    desc->type == CORESIGHT_DEV_TYPE_LINKSINK) {
		link_subtype = desc->subtype.link_subtype;

		if (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_MERG)
			nr_refcnts = desc->pdata->nr_inport;
		else if (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_SPLIT)
			nr_refcnts = desc->pdata->nr_outport;
	}

	refcnts = kcalloc(nr_refcnts, sizeof(*refcnts), GFP_KERNEL);
	if (!refcnts) {
		ret = -ENOMEM;
		goto err_free_csdev;
	}

	csdev->refcnt = refcnts;

	csdev->pdata = desc->pdata;

	csdev->type = desc->type;
	csdev->subtype = desc->subtype;
	csdev->ops = desc->ops;
	csdev->orphan = false;

	csdev->dev.type = &coresight_dev_type[desc->type];
	csdev->dev.groups = desc->groups;
	csdev->dev.parent = desc->dev;
	csdev->dev.release = coresight_device_release;
	csdev->dev.bus = &coresight_bustype;
	/*
	 * Hold the reference to our parent device. This will be
	 * dropped only in coresight_device_release().
	 */
	csdev->dev.fwnode = fwnode_handle_get(dev_fwnode(desc->dev));
	dev_set_name(&csdev->dev, "%s", desc->name);

	ret = device_register(&csdev->dev);
	if (ret) {
		put_device(&csdev->dev);
		/*
		 * All resources are free'd explicitly via
		 * coresight_device_release(), triggered from put_device().
		 */
		goto err_out;
	}

	if (csdev->type == CORESIGHT_DEV_TYPE_SINK ||
	    csdev->type == CORESIGHT_DEV_TYPE_LINKSINK) {
		ret = etm_perf_add_symlink_sink(csdev);

		if (ret) {
			device_unregister(&csdev->dev);
			/*
			 * As with the above, all resources are free'd
			 * explicitly via coresight_device_release() triggered
			 * from put_device(), which is in turn called from
			 * function device_unregister().
			 */
			goto err_out;
		}
	}

	mutex_lock(&coresight_mutex);

	coresight_fixup_device_conns(csdev);
	coresight_fixup_orphan_conns(csdev);

	mutex_unlock(&coresight_mutex);

	return csdev;

err_free_csdev:
	kfree(csdev);
err_out:
	/* Cleanup the connection information */
	coresight_release_platform_data(desc->pdata);
	return ERR_PTR(ret);
}