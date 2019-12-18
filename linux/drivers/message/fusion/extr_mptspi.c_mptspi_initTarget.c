#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {scalar_t__ inq_periph_qual; scalar_t__ type; int inquiry_len; char* inquiry; } ;
struct TYPE_12__ {scalar_t__ type; int tflags; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
typedef  TYPE_3__ VirtTarget ;
struct TYPE_13__ {TYPE_2__* ioc; } ;
struct TYPE_10__ {scalar_t__ Saf_Te; } ;
struct TYPE_11__ {TYPE_1__ spi_data; } ;
typedef  TYPE_4__ MPT_SCSI_HOST ;

/* Variables and functions */
 int MPT_TARGET_FLAGS_SAF_TE_ISSUED ; 
 scalar_t__ TYPE_PROCESSOR ; 
 int /*<<< orphan*/  mptspi_setTargetNegoParms (TYPE_4__*,TYPE_3__*,struct scsi_device*) ; 
 int /*<<< orphan*/  mptspi_writeIOCPage4 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mptspi_initTarget(MPT_SCSI_HOST *hd, VirtTarget *vtarget,
		    struct scsi_device *sdev)
{

	/* Is LUN supported? If so, upper 2 bits will be 0
	* in first byte of inquiry data.
	*/
	if (sdev->inq_periph_qual != 0)
		return;

	if (vtarget == NULL)
		return;

	vtarget->type = sdev->type;

	if ((sdev->type == TYPE_PROCESSOR) && (hd->ioc->spi_data.Saf_Te)) {
		/* Treat all Processors as SAF-TE if
		 * command line option is set */
		vtarget->tflags |= MPT_TARGET_FLAGS_SAF_TE_ISSUED;
		mptspi_writeIOCPage4(hd, vtarget->channel, vtarget->id);
	}else if ((sdev->type == TYPE_PROCESSOR) &&
		!(vtarget->tflags & MPT_TARGET_FLAGS_SAF_TE_ISSUED )) {
		if (sdev->inquiry_len > 49 ) {
			if (sdev->inquiry[44] == 'S' &&
			    sdev->inquiry[45] == 'A' &&
			    sdev->inquiry[46] == 'F' &&
			    sdev->inquiry[47] == '-' &&
			    sdev->inquiry[48] == 'T' &&
			    sdev->inquiry[49] == 'E' ) {
				vtarget->tflags |= MPT_TARGET_FLAGS_SAF_TE_ISSUED;
				mptspi_writeIOCPage4(hd, vtarget->channel, vtarget->id);
			}
		}
	}
	mptspi_setTargetNegoParms(hd, vtarget, sdev);
}