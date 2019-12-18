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
typedef  int u32 ;
struct TYPE_2__ {int spd_dpx; } ;
struct velocity_info {int mii_status; TYPE_1__ options; } ;

/* Variables and functions */
#define  SPD_DPX_1000_FULL 133 
#define  SPD_DPX_100_FULL 132 
#define  SPD_DPX_100_HALF 131 
#define  SPD_DPX_10_FULL 130 
#define  SPD_DPX_10_HALF 129 
#define  SPD_DPX_AUTO 128 
 int VELOCITY_AUTONEG_ENABLE ; 
 int VELOCITY_DUPLEX_FULL ; 
 int VELOCITY_SPEED_10 ; 
 int VELOCITY_SPEED_100 ; 
 int VELOCITY_SPEED_1000 ; 

__attribute__((used)) static u32 velocity_get_opt_media_mode(struct velocity_info *vptr)
{
	u32 status = 0;

	switch (vptr->options.spd_dpx) {
	case SPD_DPX_AUTO:
		status = VELOCITY_AUTONEG_ENABLE;
		break;
	case SPD_DPX_100_FULL:
		status = VELOCITY_SPEED_100 | VELOCITY_DUPLEX_FULL;
		break;
	case SPD_DPX_10_FULL:
		status = VELOCITY_SPEED_10 | VELOCITY_DUPLEX_FULL;
		break;
	case SPD_DPX_100_HALF:
		status = VELOCITY_SPEED_100;
		break;
	case SPD_DPX_10_HALF:
		status = VELOCITY_SPEED_10;
		break;
	case SPD_DPX_1000_FULL:
		status = VELOCITY_SPEED_1000 | VELOCITY_DUPLEX_FULL;
		break;
	}
	vptr->mii_status = status;
	return status;
}