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
struct us_data {scalar_t__ subclass; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {int no_report_luns; int pdt_1f_for_no_lun; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ USB_SC_UFI ; 
 int /*<<< orphan*/  dev_to_shost (int /*<<< orphan*/ ) ; 
 struct us_data* host_to_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int target_alloc(struct scsi_target *starget)
{
	struct us_data *us = host_to_us(dev_to_shost(starget->dev.parent));

	/*
	 * Some USB drives don't support REPORT LUNS, even though they
	 * report a SCSI revision level above 2.  Tell the SCSI layer
	 * not to issue that command; it will perform a normal sequential
	 * scan instead.
	 */
	starget->no_report_luns = 1;

	/*
	 * The UFI spec treats the Peripheral Qualifier bits in an
	 * INQUIRY result as reserved and requires devices to set them
	 * to 0.  However the SCSI spec requires these bits to be set
	 * to 3 to indicate when a LUN is not present.
	 *
	 * Let the scanning code know if this target merely sets
	 * Peripheral Device Type to 0x1f to indicate no LUN.
	 */
	if (us->subclass == USB_SC_UFI)
		starget->pdt_1f_for_no_lun = 1;

	return 0;
}