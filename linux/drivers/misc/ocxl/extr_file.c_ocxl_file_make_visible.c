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
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;
struct ocxl_file_info {TYPE_1__ dev; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ocxl_afu_fops ; 

__attribute__((used)) static int ocxl_file_make_visible(struct ocxl_file_info *info)
{
	int rc;

	cdev_init(&info->cdev, &ocxl_afu_fops);
	rc = cdev_add(&info->cdev, info->dev.devt, 1);
	if (rc) {
		dev_err(&info->dev, "Unable to add afu char device: %d\n", rc);
		return rc;
	}

	return 0;
}