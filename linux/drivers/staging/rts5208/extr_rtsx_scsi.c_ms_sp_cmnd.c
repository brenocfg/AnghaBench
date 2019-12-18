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
struct scsi_cmnd {scalar_t__* cmnd; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_MS_INFORMATION ; 
 scalar_t__ MS_FORMAT ; 
 int TRANSPORT_ERROR ; 
 int get_ms_information (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int ms_format_cmnd (struct scsi_cmnd*,struct rtsx_chip*) ; 

__attribute__((used)) static int ms_sp_cmnd(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int retval = TRANSPORT_ERROR;

	if (srb->cmnd[2] == MS_FORMAT)
		retval = ms_format_cmnd(srb, chip);
#ifdef SUPPORT_PCGL_1P18
	else if (srb->cmnd[2] == GET_MS_INFORMATION)
		retval = get_ms_information(srb, chip);
#endif

	return retval;
}