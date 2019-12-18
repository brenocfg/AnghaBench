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
struct r852_device {scalar_t__ card_registered; int /*<<< orphan*/  chip; } ;
struct mtd_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_media_type ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_engine_disable (struct r852_device*) ; 

__attribute__((used)) static void r852_unregister_nand_device(struct r852_device *dev)
{
	struct mtd_info *mtd = nand_to_mtd(dev->chip);

	if (!dev->card_registered)
		return;

	device_remove_file(&mtd->dev, &dev_attr_media_type);
	nand_release(dev->chip);
	r852_engine_disable(dev);
	dev->card_registered = 0;
}