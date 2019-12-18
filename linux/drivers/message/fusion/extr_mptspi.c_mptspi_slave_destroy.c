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
struct scsi_target {TYPE_1__* hostdata; } ;
struct scsi_device {TYPE_2__* hostdata; } ;
struct _CONFIG_PAGE_SCSI_DEVICE_1 {scalar_t__ Configuration; scalar_t__ Reserved; scalar_t__ RequestedParameters; } ;
struct TYPE_3__ {int num_luns; } ;
typedef  TYPE_1__ VirtTarget ;
struct TYPE_4__ {scalar_t__ configured_lun; } ;
typedef  TYPE_2__ VirtDevice ;

/* Variables and functions */
 int /*<<< orphan*/  mptscsih_slave_destroy (struct scsi_device*) ; 
 int /*<<< orphan*/  mptspi_write_spi_device_pg1 (struct scsi_target*,struct _CONFIG_PAGE_SCSI_DEVICE_1*) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 

__attribute__((used)) static void mptspi_slave_destroy(struct scsi_device *sdev)
{
	struct scsi_target *starget = scsi_target(sdev);
	VirtTarget *vtarget = starget->hostdata;
	VirtDevice *vdevice = sdev->hostdata;

	/* Will this be the last lun on a non-raid device? */
	if (vtarget->num_luns == 1 && vdevice->configured_lun) {
		struct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;

		/* Async Narrow */
		pg1.RequestedParameters = 0;
		pg1.Reserved = 0;
		pg1.Configuration = 0;

		mptspi_write_spi_device_pg1(starget, &pg1);
	}

	mptscsih_slave_destroy(sdev);
}