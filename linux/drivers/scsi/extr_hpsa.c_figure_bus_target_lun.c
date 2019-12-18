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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hpsa_scsi_dev_t {scalar_t__ external; int /*<<< orphan*/  rev; } ;
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 int HPSA_EXTERNAL_RAID_VOLUME_BUS ; 
 int HPSA_HBA_BUS ; 
 int HPSA_LEGACY_HBA_BUS ; 
 int HPSA_PHYSICAL_DEVICE_BUS ; 
 int HPSA_RAID_VOLUME_BUS ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpsa_set_bus_target_lun (struct hpsa_scsi_dev_t*,int,int,int) ; 
 scalar_t__ is_hba_lunid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_logical_dev_addr_mode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void figure_bus_target_lun(struct ctlr_info *h,
	u8 *lunaddrbytes, struct hpsa_scsi_dev_t *device)
{
	u32 lunid = get_unaligned_le32(lunaddrbytes);

	if (!is_logical_dev_addr_mode(lunaddrbytes)) {
		/* physical device, target and lun filled in later */
		if (is_hba_lunid(lunaddrbytes)) {
			int bus = HPSA_HBA_BUS;

			if (!device->rev)
				bus = HPSA_LEGACY_HBA_BUS;
			hpsa_set_bus_target_lun(device,
					bus, 0, lunid & 0x3fff);
		} else
			/* defer target, lun assignment for physical devices */
			hpsa_set_bus_target_lun(device,
					HPSA_PHYSICAL_DEVICE_BUS, -1, -1);
		return;
	}
	/* It's a logical device */
	if (device->external) {
		hpsa_set_bus_target_lun(device,
			HPSA_EXTERNAL_RAID_VOLUME_BUS, (lunid >> 16) & 0x3fff,
			lunid & 0x00ff);
		return;
	}
	hpsa_set_bus_target_lun(device, HPSA_RAID_VOLUME_BUS,
				0, lunid & 0x3fff);
}