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
typedef  int u8 ;
struct ext_report_lun_entry {int device_flags; int device_type; } ;
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 int BMIC_DEVICE_TYPE_ENCLOSURE ; 
 int /*<<< orphan*/  MASKED_DEVICE (int*) ; 
 int RPL_DEV_FLAG_NON_DISK ; 
 int RPL_DEV_FLAG_UNCONFIG_DISK ; 
 int RPL_DEV_FLAG_UNCONFIG_DISK_REPORTING_SUPPORTED ; 
 scalar_t__ hpsa_is_disk_spare (struct ctlr_info*,int*) ; 

__attribute__((used)) static bool hpsa_skip_device(struct ctlr_info *h, u8 *lunaddrbytes,
				struct ext_report_lun_entry *rle)
{
	u8 device_flags;
	u8 device_type;

	if (!MASKED_DEVICE(lunaddrbytes))
		return false;

	device_flags = rle->device_flags;
	device_type = rle->device_type;

	if (device_flags & RPL_DEV_FLAG_NON_DISK) {
		if (device_type == BMIC_DEVICE_TYPE_ENCLOSURE)
			return false;
		return true;
	}

	if (!(device_flags & RPL_DEV_FLAG_UNCONFIG_DISK_REPORTING_SUPPORTED))
		return false;

	if (device_flags & RPL_DEV_FLAG_UNCONFIG_DISK)
		return false;

	/*
	 * Spares may be spun down, we do not want to
	 * do an Inquiry to a RAID set spare drive as
	 * that would have them spun up, that is a
	 * performance hit because I/O to the RAID device
	 * stops while the spin up occurs which can take
	 * over 50 seconds.
	 */
	if (hpsa_is_disk_spare(h, lunaddrbytes))
		return true;

	return false;
}