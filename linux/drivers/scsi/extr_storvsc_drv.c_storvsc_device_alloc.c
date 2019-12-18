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
struct scsi_device {int sdev_bflags; } ;

/* Variables and functions */
 int BLIST_REPORTLUN2 ; 
 int BLIST_TRY_VPD_PAGES ; 

__attribute__((used)) static int storvsc_device_alloc(struct scsi_device *sdevice)
{
	/*
	 * Set blist flag to permit the reading of the VPD pages even when
	 * the target may claim SPC-2 compliance. MSFT targets currently
	 * claim SPC-2 compliance while they implement post SPC-2 features.
	 * With this flag we can correctly handle WRITE_SAME_16 issues.
	 *
	 * Hypervisor reports SCSI_UNKNOWN type for DVD ROM device but
	 * still supports REPORT LUN.
	 */
	sdevice->sdev_bflags = BLIST_REPORTLUN2 | BLIST_TRY_VPD_PAGES;

	return 0;
}