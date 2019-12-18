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
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_WRITE_ERR ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ms_rw_fail(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	if (srb->sc_data_direction == DMA_FROM_DEVICE)
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
	else
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
}