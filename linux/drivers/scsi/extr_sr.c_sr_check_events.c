#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_sense_hdr {int asc; } ;
struct scsi_cd {unsigned int get_event_changed; int ignore_get_event; int tur_changed; int media_present; scalar_t__ tur_mismatch; TYPE_1__* device; } ;
struct cdrom_device_info {struct scsi_cd* handle; } ;
struct TYPE_3__ {int changed; } ;

/* Variables and functions */
 int CDSL_CURRENT ; 
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int /*<<< orphan*/  SR_TIMEOUT ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 
 scalar_t__ scsi_status_is_good (int) ; 
 int scsi_test_unit_ready (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 unsigned int sr_get_events (TYPE_1__*) ; 
 int /*<<< orphan*/  sr_printk (int /*<<< orphan*/ ,struct scsi_cd*,char*) ; 

__attribute__((used)) static unsigned int sr_check_events(struct cdrom_device_info *cdi,
				    unsigned int clearing, int slot)
{
	struct scsi_cd *cd = cdi->handle;
	bool last_present;
	struct scsi_sense_hdr sshdr;
	unsigned int events;
	int ret;

	/* no changer support */
	if (CDSL_CURRENT != slot)
		return 0;

	events = sr_get_events(cd->device);
	cd->get_event_changed |= events & DISK_EVENT_MEDIA_CHANGE;

	/*
	 * If earlier GET_EVENT_STATUS_NOTIFICATION and TUR did not agree
	 * for several times in a row.  We rely on TUR only for this likely
	 * broken device, to prevent generating incorrect media changed
	 * events for every open().
	 */
	if (cd->ignore_get_event) {
		events &= ~DISK_EVENT_MEDIA_CHANGE;
		goto do_tur;
	}

	/*
	 * GET_EVENT_STATUS_NOTIFICATION is enough unless MEDIA_CHANGE
	 * is being cleared.  Note that there are devices which hang
	 * if asked to execute TUR repeatedly.
	 */
	if (cd->device->changed) {
		events |= DISK_EVENT_MEDIA_CHANGE;
		cd->device->changed = 0;
		cd->tur_changed = true;
	}

	if (!(clearing & DISK_EVENT_MEDIA_CHANGE))
		return events;
do_tur:
	/* let's see whether the media is there with TUR */
	last_present = cd->media_present;
	ret = scsi_test_unit_ready(cd->device, SR_TIMEOUT, MAX_RETRIES, &sshdr);

	/*
	 * Media is considered to be present if TUR succeeds or fails with
	 * sense data indicating something other than media-not-present
	 * (ASC 0x3a).
	 */
	cd->media_present = scsi_status_is_good(ret) ||
		(scsi_sense_valid(&sshdr) && sshdr.asc != 0x3a);

	if (last_present != cd->media_present)
		cd->device->changed = 1;

	if (cd->device->changed) {
		events |= DISK_EVENT_MEDIA_CHANGE;
		cd->device->changed = 0;
		cd->tur_changed = true;
	}

	if (cd->ignore_get_event)
		return events;

	/* check whether GET_EVENT is reporting spurious MEDIA_CHANGE */
	if (!cd->tur_changed) {
		if (cd->get_event_changed) {
			if (cd->tur_mismatch++ > 8) {
				sr_printk(KERN_WARNING, cd,
					  "GET_EVENT and TUR disagree continuously, suppress GET_EVENT events\n");
				cd->ignore_get_event = true;
			}
		} else {
			cd->tur_mismatch = 0;
		}
	}
	cd->tur_changed = false;
	cd->get_event_changed = false;

	return events;
}