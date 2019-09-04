#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  devnode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  OCXL_NUM_MINORS ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minors_idr ; 
 int /*<<< orphan*/  minors_idr_lock ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* ocxl_class ; 
 int /*<<< orphan*/  ocxl_dev ; 
 int /*<<< orphan*/  ocxl_devnode ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ocxl_file_init(void)
{
	int rc;

	mutex_init(&minors_idr_lock);
	idr_init(&minors_idr);

	rc = alloc_chrdev_region(&ocxl_dev, 0, OCXL_NUM_MINORS, "ocxl");
	if (rc) {
		pr_err("Unable to allocate ocxl major number: %d\n", rc);
		return rc;
	}

	ocxl_class = class_create(THIS_MODULE, "ocxl");
	if (IS_ERR(ocxl_class)) {
		pr_err("Unable to create ocxl class\n");
		unregister_chrdev_region(ocxl_dev, OCXL_NUM_MINORS);
		return PTR_ERR(ocxl_class);
	}

	ocxl_class->devnode = ocxl_devnode;
	return 0;
}