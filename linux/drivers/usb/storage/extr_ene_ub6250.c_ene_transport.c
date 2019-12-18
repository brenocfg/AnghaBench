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
struct us_data {scalar_t__ extra; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_4__ {scalar_t__ Ready; } ;
struct TYPE_3__ {scalar_t__ Ready; } ;
struct ene_ub6250_info {TYPE_2__ MS_Status; TYPE_1__ SD_Status; } ;

/* Variables and functions */
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_XFER_GOOD ; 
 int ene_init (struct us_data*) ; 
 int ms_scsi_irp (struct us_data*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int sd_scsi_irp (struct us_data*,struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ene_transport(struct scsi_cmnd *srb, struct us_data *us)
{
	int result = USB_STOR_XFER_GOOD;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *)(us->extra);

	/*US_DEBUG(usb_stor_show_command(us, srb)); */
	scsi_set_resid(srb, 0);
	if (unlikely(!(info->SD_Status.Ready || info->MS_Status.Ready)))
		result = ene_init(us);
	if (result == USB_STOR_XFER_GOOD) {
		result = USB_STOR_TRANSPORT_ERROR;
		if (info->SD_Status.Ready)
			result = sd_scsi_irp(us, srb);

		if (info->MS_Status.Ready)
			result = ms_scsi_irp(us, srb);
	}
	return result;
}