#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; } ;
struct TYPE_6__ {int link_subtype; } ;
struct coresight_device {int nr_inport; int nr_outport; size_t type; int orphan; TYPE_3__ dev; int /*<<< orphan*/  ops; TYPE_1__ subtype; struct coresight_connection* conns; struct coresight_device* refcnt; } ;
struct coresight_desc {size_t type; TYPE_2__* pdata; int /*<<< orphan*/  dev; int /*<<< orphan*/  groups; int /*<<< orphan*/  ops; TYPE_1__ subtype; } ;
struct coresight_connection {int /*<<< orphan*/  child_port; int /*<<< orphan*/  child_name; int /*<<< orphan*/  outport; } ;
typedef  struct coresight_device atomic_t ;
struct TYPE_7__ {int nr_inport; int nr_outport; int /*<<< orphan*/  name; int /*<<< orphan*/ * child_ports; int /*<<< orphan*/ * child_names; int /*<<< orphan*/ * outports; } ;

/* Variables and functions */
 int CORESIGHT_DEV_SUBTYPE_LINK_MERG ; 
 int CORESIGHT_DEV_SUBTYPE_LINK_SPLIT ; 
 size_t CORESIGHT_DEV_TYPE_LINK ; 
 size_t CORESIGHT_DEV_TYPE_LINKSINK ; 
 int ENOMEM ; 
 struct coresight_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  coresight_bustype ; 
 int /*<<< orphan*/ * coresight_dev_type ; 
 int /*<<< orphan*/  coresight_device_release ; 
 int /*<<< orphan*/  coresight_fixup_device_conns (struct coresight_device*) ; 
 int /*<<< orphan*/  coresight_fixup_orphan_conns (struct coresight_device*) ; 
 int /*<<< orphan*/  coresight_mutex ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_3__*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct coresight_device*) ; 
 struct coresight_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 

struct coresight_device *coresight_register(struct coresight_desc *desc)
{
	int i;
	int ret;
	int link_subtype;
	int nr_refcnts = 1;
	atomic_t *refcnts = NULL;
	struct coresight_device *csdev;
	struct coresight_connection *conns = NULL;

	csdev = kzalloc(sizeof(*csdev), GFP_KERNEL);
	if (!csdev) {
		ret = -ENOMEM;
		goto err_kzalloc_csdev;
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
		goto err_kzalloc_refcnts;
	}

	csdev->refcnt = refcnts;

	csdev->nr_inport = desc->pdata->nr_inport;
	csdev->nr_outport = desc->pdata->nr_outport;

	/* Initialise connections if there is at least one outport */
	if (csdev->nr_outport) {
		conns = kcalloc(csdev->nr_outport, sizeof(*conns), GFP_KERNEL);
		if (!conns) {
			ret = -ENOMEM;
			goto err_kzalloc_conns;
		}

		for (i = 0; i < csdev->nr_outport; i++) {
			conns[i].outport = desc->pdata->outports[i];
			conns[i].child_name = desc->pdata->child_names[i];
			conns[i].child_port = desc->pdata->child_ports[i];
		}
	}

	csdev->conns = conns;

	csdev->type = desc->type;
	csdev->subtype = desc->subtype;
	csdev->ops = desc->ops;
	csdev->orphan = false;

	csdev->dev.type = &coresight_dev_type[desc->type];
	csdev->dev.groups = desc->groups;
	csdev->dev.parent = desc->dev;
	csdev->dev.release = coresight_device_release;
	csdev->dev.bus = &coresight_bustype;
	dev_set_name(&csdev->dev, "%s", desc->pdata->name);

	ret = device_register(&csdev->dev);
	if (ret) {
		put_device(&csdev->dev);
		goto err_kzalloc_csdev;
	}

	mutex_lock(&coresight_mutex);

	coresight_fixup_device_conns(csdev);
	coresight_fixup_orphan_conns(csdev);

	mutex_unlock(&coresight_mutex);

	return csdev;

err_kzalloc_conns:
	kfree(refcnts);
err_kzalloc_refcnts:
	kfree(csdev);
err_kzalloc_csdev:
	return ERR_PTR(ret);
}