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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int flags; } ;
struct ata_eh_context {TYPE_2__ i; } ;
struct ata_device {int flags; scalar_t__ class; int horkage; int /*<<< orphan*/  id; scalar_t__ n_native_sectors; TYPE_1__* link; } ;
struct TYPE_3__ {struct ata_eh_context eh_context; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 scalar_t__ ATA_DEV_ZAC ; 
 int ATA_DFLAG_UNLOCK_HPA ; 
 int ATA_EHI_PRINTINFO ; 
 int ATA_HORKAGE_BROKEN_HPA ; 
 int EACCES ; 
 int /*<<< orphan*/  ata_dev_err (struct ata_device*,char*) ; 
 int /*<<< orphan*/  ata_dev_info (struct ata_device*,char*,unsigned long long,unsigned long long,...) ; 
 int ata_dev_reread_id (struct ata_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*,...) ; 
 int /*<<< orphan*/  ata_id_has_lba (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_id_hpa_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_n_sectors (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_ignore_hpa ; 
 int ata_read_native_max_address (struct ata_device*,scalar_t__*) ; 
 int ata_set_max_sectors (struct ata_device*,scalar_t__) ; 

__attribute__((used)) static int ata_hpa_resize(struct ata_device *dev)
{
	struct ata_eh_context *ehc = &dev->link->eh_context;
	int print_info = ehc->i.flags & ATA_EHI_PRINTINFO;
	bool unlock_hpa = ata_ignore_hpa || dev->flags & ATA_DFLAG_UNLOCK_HPA;
	u64 sectors = ata_id_n_sectors(dev->id);
	u64 native_sectors;
	int rc;

	/* do we need to do it? */
	if ((dev->class != ATA_DEV_ATA && dev->class != ATA_DEV_ZAC) ||
	    !ata_id_has_lba(dev->id) || !ata_id_hpa_enabled(dev->id) ||
	    (dev->horkage & ATA_HORKAGE_BROKEN_HPA))
		return 0;

	/* read native max address */
	rc = ata_read_native_max_address(dev, &native_sectors);
	if (rc) {
		/* If device aborted the command or HPA isn't going to
		 * be unlocked, skip HPA resizing.
		 */
		if (rc == -EACCES || !unlock_hpa) {
			ata_dev_warn(dev,
				     "HPA support seems broken, skipping HPA handling\n");
			dev->horkage |= ATA_HORKAGE_BROKEN_HPA;

			/* we can continue if device aborted the command */
			if (rc == -EACCES)
				rc = 0;
		}

		return rc;
	}
	dev->n_native_sectors = native_sectors;

	/* nothing to do? */
	if (native_sectors <= sectors || !unlock_hpa) {
		if (!print_info || native_sectors == sectors)
			return 0;

		if (native_sectors > sectors)
			ata_dev_info(dev,
				"HPA detected: current %llu, native %llu\n",
				(unsigned long long)sectors,
				(unsigned long long)native_sectors);
		else if (native_sectors < sectors)
			ata_dev_warn(dev,
				"native sectors (%llu) is smaller than sectors (%llu)\n",
				(unsigned long long)native_sectors,
				(unsigned long long)sectors);
		return 0;
	}

	/* let's unlock HPA */
	rc = ata_set_max_sectors(dev, native_sectors);
	if (rc == -EACCES) {
		/* if device aborted the command, skip HPA resizing */
		ata_dev_warn(dev,
			     "device aborted resize (%llu -> %llu), skipping HPA handling\n",
			     (unsigned long long)sectors,
			     (unsigned long long)native_sectors);
		dev->horkage |= ATA_HORKAGE_BROKEN_HPA;
		return 0;
	} else if (rc)
		return rc;

	/* re-read IDENTIFY data */
	rc = ata_dev_reread_id(dev, 0);
	if (rc) {
		ata_dev_err(dev,
			    "failed to re-read IDENTIFY data after HPA resizing\n");
		return rc;
	}

	if (print_info) {
		u64 new_sectors = ata_id_n_sectors(dev->id);
		ata_dev_info(dev,
			"HPA unlocked: %llu -> %llu, native %llu\n",
			(unsigned long long)sectors,
			(unsigned long long)new_sectors,
			(unsigned long long)native_sectors);
	}

	return 0;
}