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
struct gasket_internal_desc {int /*<<< orphan*/  class; } ;
struct TYPE_2__ {int /*<<< orphan*/  devt; int /*<<< orphan*/  device; } ;
struct gasket_dev {TYPE_1__ dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_free_dev (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_sysfs_remove_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __gasket_remove_device(struct gasket_internal_desc *internal_desc,
				   struct gasket_dev *gasket_dev)
{
	gasket_sysfs_remove_mapping(gasket_dev->dev_info.device);
	device_destroy(internal_desc->class, gasket_dev->dev_info.devt);
	gasket_free_dev(gasket_dev);
}