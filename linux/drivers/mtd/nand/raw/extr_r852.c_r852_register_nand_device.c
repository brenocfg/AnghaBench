#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct r852_device {int card_registered; scalar_t__ card_detected; TYPE_2__* chip; int /*<<< orphan*/  sm; scalar_t__ readonly; TYPE_1__* pci_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct mtd_info {TYPE_4__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  options; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ROM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_attr_media_type ; 
 scalar_t__ device_create_file (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  message (char*) ; 
 int /*<<< orphan*/  nand_release (TYPE_2__*) ; 
 struct mtd_info* nand_to_mtd (TYPE_2__*) ; 
 int /*<<< orphan*/  r852_engine_enable (struct r852_device*) ; 
 scalar_t__ sm_register_device (struct mtd_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r852_register_nand_device(struct r852_device *dev)
{
	struct mtd_info *mtd = nand_to_mtd(dev->chip);

	WARN_ON(dev->card_registered);

	mtd->dev.parent = &dev->pci_dev->dev;

	if (dev->readonly)
		dev->chip->options |= NAND_ROM;

	r852_engine_enable(dev);

	if (sm_register_device(mtd, dev->sm))
		goto error1;

	if (device_create_file(&mtd->dev, &dev_attr_media_type)) {
		message("can't create media type sysfs attribute");
		goto error3;
	}

	dev->card_registered = 1;
	return 0;
error3:
	nand_release(dev->chip);
error1:
	/* Force card redetect */
	dev->card_detected = 0;
	return -1;
}