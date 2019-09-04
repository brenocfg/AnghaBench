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
typedef  unsigned int u8 ;
struct ata_port {unsigned int* sector_buf; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_2__ {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_LOG_IDENTIFY_DEVICE ; 
 int /*<<< orphan*/  ata_dev_info (struct ata_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 
 int /*<<< orphan*/  ata_log_supported (struct ata_device*,int /*<<< orphan*/ ) ; 
 unsigned int ata_read_log_page (struct ata_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static bool ata_identify_page_supported(struct ata_device *dev, u8 page)
{
	struct ata_port *ap = dev->link->ap;
	unsigned int err, i;

	if (!ata_log_supported(dev, ATA_LOG_IDENTIFY_DEVICE)) {
		ata_dev_warn(dev, "ATA Identify Device Log not supported\n");
		return false;
	}

	/*
	 * Read IDENTIFY DEVICE data log, page 0, to figure out if the page is
	 * supported.
	 */
	err = ata_read_log_page(dev, ATA_LOG_IDENTIFY_DEVICE, 0, ap->sector_buf,
				1);
	if (err) {
		ata_dev_info(dev,
			     "failed to get Device Identify Log Emask 0x%x\n",
			     err);
		return false;
	}

	for (i = 0; i < ap->sector_buf[8]; i++) {
		if (ap->sector_buf[9 + i] == page)
			return true;
	}

	return false;
}