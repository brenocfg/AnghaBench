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
typedef  unsigned long long u64 ;
struct ata_port {int /*<<< orphan*/ * sector_buf; } ;
struct ata_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  id; TYPE_1__* link; } ;
struct TYPE_2__ {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DFLAG_TRUSTED ; 
 int /*<<< orphan*/  ATA_LOG_IDENTIFY_DEVICE ; 
 int /*<<< orphan*/  ATA_LOG_SECURITY ; 
 int /*<<< orphan*/  ata_dev_dbg (struct ata_device*,char*,...) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 
 int /*<<< orphan*/  ata_id_has_trusted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_identify_page_supported (struct ata_device*,int /*<<< orphan*/ ) ; 
 unsigned int ata_read_log_page (struct ata_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 unsigned long long get_unaligned_le64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ata_dev_config_trusted(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;
	u64 trusted_cap;
	unsigned int err;

	if (!ata_id_has_trusted(dev->id))
		return;

	if (!ata_identify_page_supported(dev, ATA_LOG_SECURITY)) {
		ata_dev_warn(dev,
			     "Security Log not supported\n");
		return;
	}

	err = ata_read_log_page(dev, ATA_LOG_IDENTIFY_DEVICE, ATA_LOG_SECURITY,
			ap->sector_buf, 1);
	if (err) {
		ata_dev_dbg(dev,
			    "failed to read Security Log, Emask 0x%x\n", err);
		return;
	}

	trusted_cap = get_unaligned_le64(&ap->sector_buf[40]);
	if (!(trusted_cap & (1ULL << 63))) {
		ata_dev_dbg(dev,
			    "Trusted Computing capability qword not valid!\n");
		return;
	}

	if (trusted_cap & (1 << 0))
		dev->flags |= ATA_DFLAG_TRUSTED;
}