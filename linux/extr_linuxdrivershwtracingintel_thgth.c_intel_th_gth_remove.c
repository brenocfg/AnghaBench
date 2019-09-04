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
struct intel_th_device {int /*<<< orphan*/  dev; } ;
struct gth_device {int /*<<< orphan*/  master_group; TYPE_1__* dev; int /*<<< orphan*/  output_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 struct gth_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_th_gth_remove(struct intel_th_device *thdev)
{
	struct gth_device *gth = dev_get_drvdata(&thdev->dev);

	sysfs_remove_group(&gth->dev->kobj, &gth->output_group);
	sysfs_remove_group(&gth->dev->kobj, &gth->master_group);
}