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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ocxl_fn {TYPE_1__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/  class; int /*<<< orphan*/  devt; TYPE_1__* parent; } ;
struct ocxl_file_info {TYPE_3__ dev; struct ocxl_afu* afu; } ;
struct TYPE_7__ {int /*<<< orphan*/  idx; int /*<<< orphan*/  name; } ;
struct ocxl_afu {TYPE_2__ config; struct ocxl_fn* fn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int allocate_minor (struct ocxl_file_info*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  free_minor (struct ocxl_file_info*) ; 
 int /*<<< orphan*/  info_release ; 
 int /*<<< orphan*/  kfree (struct ocxl_file_info*) ; 
 struct ocxl_file_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocxl_afu_get (struct ocxl_afu*) ; 
 int /*<<< orphan*/  ocxl_afu_put (struct ocxl_afu*) ; 
 int /*<<< orphan*/  ocxl_afu_set_private (struct ocxl_afu*,struct ocxl_file_info*) ; 
 int /*<<< orphan*/  ocxl_class ; 
 int /*<<< orphan*/  ocxl_dev ; 
 int ocxl_file_make_visible (struct ocxl_file_info*) ; 
 int ocxl_sysfs_register_afu (struct ocxl_file_info*) ; 
 int /*<<< orphan*/  ocxl_sysfs_unregister_afu (struct ocxl_file_info*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

int ocxl_file_register_afu(struct ocxl_afu *afu)
{
	int minor;
	int rc;
	struct ocxl_file_info *info;
	struct ocxl_fn *fn = afu->fn;
	struct pci_dev *pci_dev = to_pci_dev(fn->dev.parent);

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL)
		return -ENOMEM;

	minor = allocate_minor(info);
	if (minor < 0) {
		kfree(info);
		return minor;
	}

	info->dev.parent = &fn->dev;
	info->dev.devt = MKDEV(MAJOR(ocxl_dev), minor);
	info->dev.class = ocxl_class;
	info->dev.release = info_release;

	info->afu = afu;
	ocxl_afu_get(afu);

	rc = dev_set_name(&info->dev, "%s.%s.%hhu",
		afu->config.name, dev_name(&pci_dev->dev), afu->config.idx);
	if (rc)
		goto err_put;

	rc = device_register(&info->dev);
	if (rc)
		goto err_put;

	rc = ocxl_sysfs_register_afu(info);
	if (rc)
		goto err_unregister;

	rc = ocxl_file_make_visible(info);
	if (rc)
		goto err_unregister;

	ocxl_afu_set_private(afu, info);

	return 0;

err_unregister:
	ocxl_sysfs_unregister_afu(info); // safe to call even if register failed
	device_unregister(&info->dev);
err_put:
	ocxl_afu_put(afu);
	free_minor(info);
	kfree(info);
	return rc;
}