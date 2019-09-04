#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cosm_device {int /*<<< orphan*/  attr_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  cosm_default_groups ; 

void cosm_sysfs_init(struct cosm_device *cdev)
{
	cdev->attr_group = cosm_default_groups;
}