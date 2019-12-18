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
struct scsi_mode_data {int device_specific; } ;
struct scsi_disk {int write_prot; scalar_t__ first_scan; int /*<<< orphan*/  disk; struct scsi_device* device; } ;
struct scsi_device {scalar_t__ use_192_bytes_for_3f; scalar_t__ skip_ms_page_3f; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  scsi_status_is_good (int) ; 
 int sd_do_mode_sense (struct scsi_device*,int /*<<< orphan*/ ,int,unsigned char*,int,struct scsi_mode_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_first_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,...) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sd_read_write_protect_flag(struct scsi_disk *sdkp, unsigned char *buffer)
{
	int res;
	struct scsi_device *sdp = sdkp->device;
	struct scsi_mode_data data;
	int old_wp = sdkp->write_prot;

	set_disk_ro(sdkp->disk, 0);
	if (sdp->skip_ms_page_3f) {
		sd_first_printk(KERN_NOTICE, sdkp, "Assuming Write Enabled\n");
		return;
	}

	if (sdp->use_192_bytes_for_3f) {
		res = sd_do_mode_sense(sdp, 0, 0x3F, buffer, 192, &data, NULL);
	} else {
		/*
		 * First attempt: ask for all pages (0x3F), but only 4 bytes.
		 * We have to start carefully: some devices hang if we ask
		 * for more than is available.
		 */
		res = sd_do_mode_sense(sdp, 0, 0x3F, buffer, 4, &data, NULL);

		/*
		 * Second attempt: ask for page 0 When only page 0 is
		 * implemented, a request for page 3F may return Sense Key
		 * 5: Illegal Request, Sense Code 24: Invalid field in
		 * CDB.
		 */
		if (!scsi_status_is_good(res))
			res = sd_do_mode_sense(sdp, 0, 0, buffer, 4, &data, NULL);

		/*
		 * Third attempt: ask 255 bytes, as we did earlier.
		 */
		if (!scsi_status_is_good(res))
			res = sd_do_mode_sense(sdp, 0, 0x3F, buffer, 255,
					       &data, NULL);
	}

	if (!scsi_status_is_good(res)) {
		sd_first_printk(KERN_WARNING, sdkp,
			  "Test WP failed, assume Write Enabled\n");
	} else {
		sdkp->write_prot = ((data.device_specific & 0x80) != 0);
		set_disk_ro(sdkp->disk, sdkp->write_prot);
		if (sdkp->first_scan || old_wp != sdkp->write_prot) {
			sd_printk(KERN_NOTICE, sdkp, "Write Protect is %s\n",
				  sdkp->write_prot ? "on" : "off");
			sd_printk(KERN_DEBUG, sdkp, "Mode Sense: %4ph\n", buffer);
		}
	}
}