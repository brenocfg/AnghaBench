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
struct idt_89hpesx_dev {scalar_t__ eesize; int /*<<< orphan*/  ee_file; TYPE_1__* client; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idt_remove_sysfs_files(struct idt_89hpesx_dev *pdev)
{
	struct device *dev = &pdev->client->dev;

	/* Don't do anything if EEPROM wasn't accessible */
	if (pdev->eesize == 0)
		return;

	/* Remove EEPROM sysfs file */
	sysfs_remove_bin_file(&dev->kobj, pdev->ee_file);
}