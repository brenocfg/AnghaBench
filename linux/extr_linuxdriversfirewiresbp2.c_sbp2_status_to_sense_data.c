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
typedef  int u8 ;

/* Variables and functions */
 int DID_ERROR ; 
 int DID_OK ; 
#define  SAM_STAT_BUSY 133 
#define  SAM_STAT_CHECK_CONDITION 132 
#define  SAM_STAT_COMMAND_TERMINATED 131 
#define  SAM_STAT_CONDITION_MET 130 
#define  SAM_STAT_GOOD 129 
#define  SAM_STAT_RESERVATION_CONFLICT 128 

__attribute__((used)) static unsigned int sbp2_status_to_sense_data(u8 *sbp2_status, u8 *sense_data)
{
	int sam_status;
	int sfmt = (sbp2_status[0] >> 6) & 0x03;

	if (sfmt == 2 || sfmt == 3) {
		/*
		 * Reserved for future standardization (2) or
		 * Status block format vendor-dependent (3)
		 */
		return DID_ERROR << 16;
	}

	sense_data[0] = 0x70 | sfmt | (sbp2_status[1] & 0x80);
	sense_data[1] = 0x0;
	sense_data[2] = ((sbp2_status[1] << 1) & 0xe0) | (sbp2_status[1] & 0x0f);
	sense_data[3] = sbp2_status[4];
	sense_data[4] = sbp2_status[5];
	sense_data[5] = sbp2_status[6];
	sense_data[6] = sbp2_status[7];
	sense_data[7] = 10;
	sense_data[8] = sbp2_status[8];
	sense_data[9] = sbp2_status[9];
	sense_data[10] = sbp2_status[10];
	sense_data[11] = sbp2_status[11];
	sense_data[12] = sbp2_status[2];
	sense_data[13] = sbp2_status[3];
	sense_data[14] = sbp2_status[12];
	sense_data[15] = sbp2_status[13];

	sam_status = sbp2_status[0] & 0x3f;

	switch (sam_status) {
	case SAM_STAT_GOOD:
	case SAM_STAT_CHECK_CONDITION:
	case SAM_STAT_CONDITION_MET:
	case SAM_STAT_BUSY:
	case SAM_STAT_RESERVATION_CONFLICT:
	case SAM_STAT_COMMAND_TERMINATED:
		return DID_OK << 16 | sam_status;

	default:
		return DID_ERROR << 16;
	}
}