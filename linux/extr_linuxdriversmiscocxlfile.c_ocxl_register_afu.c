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
struct TYPE_2__ {int /*<<< orphan*/  class; int /*<<< orphan*/  devt; } ;
struct ocxl_afu {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int allocate_afu_minor (struct ocxl_afu*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  ocxl_class ; 
 int /*<<< orphan*/  ocxl_dev ; 

int ocxl_register_afu(struct ocxl_afu *afu)
{
	int minor;

	minor = allocate_afu_minor(afu);
	if (minor < 0)
		return minor;
	afu->dev.devt = MKDEV(MAJOR(ocxl_dev), minor);
	afu->dev.class = ocxl_class;
	return device_register(&afu->dev);
}