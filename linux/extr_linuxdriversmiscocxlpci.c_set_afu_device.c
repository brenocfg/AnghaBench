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
struct ocxl_fn {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idx; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct ocxl_afu {TYPE_1__ config; TYPE_2__ dev; struct ocxl_fn* fn; } ;

/* Variables and functions */
 int dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_afu_dev ; 

__attribute__((used)) static int set_afu_device(struct ocxl_afu *afu, const char *location)
{
	struct ocxl_fn *fn = afu->fn;
	int rc;

	afu->dev.parent = &fn->dev;
	afu->dev.release = free_afu_dev;
	rc = dev_set_name(&afu->dev, "%s.%s.%hhu", afu->config.name, location,
		afu->config.idx);
	return rc;
}