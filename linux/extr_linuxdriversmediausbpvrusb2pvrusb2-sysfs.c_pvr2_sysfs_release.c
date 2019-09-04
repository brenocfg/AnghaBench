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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct device*) ; 
 int /*<<< orphan*/  pvr2_sysfs_trace (char*,struct device*) ; 

__attribute__((used)) static void pvr2_sysfs_release(struct device *class_dev)
{
	pvr2_sysfs_trace("Releasing class_dev id=%p",class_dev);
	kfree(class_dev);
}