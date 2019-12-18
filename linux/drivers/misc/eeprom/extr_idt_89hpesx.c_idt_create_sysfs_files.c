#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct idt_89hpesx_dev {scalar_t__ eesize; TYPE_3__* ee_file; scalar_t__ eero; TYPE_1__* client; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {int mode; } ;
struct TYPE_8__ {scalar_t__ size; int /*<<< orphan*/ * write; TYPE_2__ attr; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bin_attr_eeprom ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 TYPE_3__* devm_kmalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int idt_create_sysfs_files(struct idt_89hpesx_dev *pdev)
{
	struct device *dev = &pdev->client->dev;
	int ret;

	/* Don't do anything if EEPROM isn't accessible */
	if (pdev->eesize == 0) {
		dev_dbg(dev, "Skip creating sysfs-files");
		return 0;
	}

	/* Allocate memory for attribute file */
	pdev->ee_file = devm_kmalloc(dev, sizeof(*pdev->ee_file), GFP_KERNEL);
	if (!pdev->ee_file)
		return -ENOMEM;

	/* Copy the declared EEPROM attr structure to change some of fields */
	memcpy(pdev->ee_file, &bin_attr_eeprom, sizeof(*pdev->ee_file));

	/* In case of read-only EEPROM get rid of write ability */
	if (pdev->eero) {
		pdev->ee_file->attr.mode &= ~0200;
		pdev->ee_file->write = NULL;
	}
	/* Create EEPROM sysfs file */
	pdev->ee_file->size = pdev->eesize;
	ret = sysfs_create_bin_file(&dev->kobj, pdev->ee_file);
	if (ret != 0) {
		dev_err(dev, "Failed to create EEPROM sysfs-node");
		return ret;
	}

	return 0;
}