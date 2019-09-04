#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  mmap; int /*<<< orphan*/  read; int /*<<< orphan*/  size; TYPE_2__ attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  global_mmio_size; } ;
struct ocxl_afu {int /*<<< orphan*/  dev; TYPE_3__ attr_global_mmio; TYPE_1__ config; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * afu_attrs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_create_bin_file (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_mmio_mmap ; 
 int /*<<< orphan*/  global_mmio_read ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

int ocxl_sysfs_add_afu(struct ocxl_afu *afu)
{
	int i, rc;

	for (i = 0; i < ARRAY_SIZE(afu_attrs); i++) {
		rc = device_create_file(&afu->dev, &afu_attrs[i]);
		if (rc)
			goto err;
	}

	sysfs_attr_init(&afu->attr_global_mmio.attr);
	afu->attr_global_mmio.attr.name = "global_mmio_area";
	afu->attr_global_mmio.attr.mode = 0600;
	afu->attr_global_mmio.size = afu->config.global_mmio_size;
	afu->attr_global_mmio.read = global_mmio_read;
	afu->attr_global_mmio.mmap = global_mmio_mmap;
	rc = device_create_bin_file(&afu->dev, &afu->attr_global_mmio);
	if (rc) {
		dev_err(&afu->dev,
			"Unable to create global mmio attr for afu: %d\n",
			rc);
		goto err;
	}

	return 0;

err:
	for (i--; i >= 0; i--)
		device_remove_file(&afu->dev, &afu_attrs[i]);
	return rc;
}