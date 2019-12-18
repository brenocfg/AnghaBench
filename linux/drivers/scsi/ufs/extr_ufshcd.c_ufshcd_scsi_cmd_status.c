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
struct ufshcd_lrb {int dummy; } ;

/* Variables and functions */
 int COMMAND_COMPLETE ; 
 int DID_ERROR ; 
 int DID_OK ; 
#define  SAM_STAT_BUSY 132 
#define  SAM_STAT_CHECK_CONDITION 131 
#define  SAM_STAT_GOOD 130 
#define  SAM_STAT_TASK_ABORTED 129 
#define  SAM_STAT_TASK_SET_FULL 128 
 int /*<<< orphan*/  ufshcd_copy_sense_data (struct ufshcd_lrb*) ; 

__attribute__((used)) static inline int
ufshcd_scsi_cmd_status(struct ufshcd_lrb *lrbp, int scsi_status)
{
	int result = 0;

	switch (scsi_status) {
	case SAM_STAT_CHECK_CONDITION:
		ufshcd_copy_sense_data(lrbp);
		/* fallthrough */
	case SAM_STAT_GOOD:
		result |= DID_OK << 16 |
			  COMMAND_COMPLETE << 8 |
			  scsi_status;
		break;
	case SAM_STAT_TASK_SET_FULL:
	case SAM_STAT_BUSY:
	case SAM_STAT_TASK_ABORTED:
		ufshcd_copy_sense_data(lrbp);
		result |= scsi_status;
		break;
	default:
		result |= DID_ERROR << 16;
		break;
	} /* end of switch */

	return result;
}