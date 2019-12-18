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

/* Variables and functions */
#define  SCSI_ACCESS_STATE_ACTIVE 134 
#define  SCSI_ACCESS_STATE_LBA 133 
#define  SCSI_ACCESS_STATE_OFFLINE 132 
#define  SCSI_ACCESS_STATE_OPTIMAL 131 
#define  SCSI_ACCESS_STATE_STANDBY 130 
#define  SCSI_ACCESS_STATE_TRANSITIONING 129 
#define  SCSI_ACCESS_STATE_UNAVAILABLE 128 

__attribute__((used)) static char print_alua_state(unsigned char state)
{
	switch (state) {
	case SCSI_ACCESS_STATE_OPTIMAL:
		return 'A';
	case SCSI_ACCESS_STATE_ACTIVE:
		return 'N';
	case SCSI_ACCESS_STATE_STANDBY:
		return 'S';
	case SCSI_ACCESS_STATE_UNAVAILABLE:
		return 'U';
	case SCSI_ACCESS_STATE_LBA:
		return 'L';
	case SCSI_ACCESS_STATE_OFFLINE:
		return 'O';
	case SCSI_ACCESS_STATE_TRANSITIONING:
		return 'T';
	default:
		return 'X';
	}
}