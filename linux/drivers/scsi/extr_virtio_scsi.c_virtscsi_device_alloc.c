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
struct scsi_device {int /*<<< orphan*/  sdev_bflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLIST_TRY_VPD_PAGES ; 

__attribute__((used)) static int virtscsi_device_alloc(struct scsi_device *sdevice)
{
	/*
	 * Passed through SCSI targets (e.g. with qemu's 'scsi-block')
	 * may have transfer limits which come from the host SCSI
	 * controller or something on the host side other than the
	 * target itself.
	 *
	 * To make this work properly, the hypervisor can adjust the
	 * target's VPD information to advertise these limits.  But
	 * for that to work, the guest has to look at the VPD pages,
	 * which we won't do by default if it is an SPC-2 device, even
	 * if it does actually support it.
	 *
	 * So, set the blist to always try to read the VPD pages.
	 */
	sdevice->sdev_bflags = BLIST_TRY_VPD_PAGES;

	return 0;
}