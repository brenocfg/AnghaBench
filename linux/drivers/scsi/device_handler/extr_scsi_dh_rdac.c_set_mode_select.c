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
struct scsi_device {int dummy; } ;
struct c2_inquiry {scalar_t__ max_lun_supported; } ;
struct TYPE_3__ {struct c2_inquiry c2; } ;
struct rdac_dh_data {TYPE_2__* ctlr; TYPE_1__ inq; } ;
struct TYPE_4__ {int use_ms10; } ;

/* Variables and functions */
 scalar_t__ MODE6_MAX_LUN ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_OK ; 
 int /*<<< orphan*/  scsi_get_vpd_page (struct scsi_device*,int,unsigned char*,int) ; 

__attribute__((used)) static int set_mode_select(struct scsi_device *sdev, struct rdac_dh_data *h)
{
	int err = SCSI_DH_IO;
	struct c2_inquiry *inqp = &h->inq.c2;

	if (!scsi_get_vpd_page(sdev, 0xC2, (unsigned char *)inqp,
			       sizeof(struct c2_inquiry))) {
		/*
		 * If more than MODE6_MAX_LUN luns are supported, use
		 * mode select 10
		 */
		if (inqp->max_lun_supported >= MODE6_MAX_LUN)
			h->ctlr->use_ms10 = 1;
		else
			h->ctlr->use_ms10 = 0;
		err = SCSI_DH_OK;
	}
	return err;
}