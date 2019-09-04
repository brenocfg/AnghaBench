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
struct ata_device {struct device tdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_tdev_free (struct ata_device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  transport_remove_device (struct device*) ; 

__attribute__((used)) static void ata_tdev_delete(struct ata_device *ata_dev)
{
	struct device *dev = &ata_dev->tdev;

	transport_remove_device(dev);
	device_del(dev);
	ata_tdev_free(ata_dev);
}