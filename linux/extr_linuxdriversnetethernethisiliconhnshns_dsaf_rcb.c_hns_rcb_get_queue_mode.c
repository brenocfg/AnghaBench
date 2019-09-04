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
typedef  int u16 ;
typedef  enum dsaf_mode { ____Placeholder_dsaf_mode } dsaf_mode ;

/* Variables and functions */
#define  DSAF_MODE_DISABLE_2PORT_64VM 132 
#define  DSAF_MODE_DISABLE_6PORT_0VM 131 
#define  DSAF_MODE_DISABLE_6PORT_16VM 130 
#define  DSAF_MODE_DISABLE_FIX 129 
#define  DSAF_MODE_DISABLE_SP 128 

void hns_rcb_get_queue_mode(enum dsaf_mode dsaf_mode, u16 *max_vfn,
			    u16 *max_q_per_vf)
{
	switch (dsaf_mode) {
	case DSAF_MODE_DISABLE_6PORT_0VM:
		*max_vfn = 1;
		*max_q_per_vf = 16;
		break;
	case DSAF_MODE_DISABLE_FIX:
	case DSAF_MODE_DISABLE_SP:
		*max_vfn = 1;
		*max_q_per_vf = 1;
		break;
	case DSAF_MODE_DISABLE_2PORT_64VM:
		*max_vfn = 64;
		*max_q_per_vf = 1;
		break;
	case DSAF_MODE_DISABLE_6PORT_16VM:
		*max_vfn = 16;
		*max_q_per_vf = 1;
		break;
	default:
		*max_vfn = 1;
		*max_q_per_vf = 16;
		break;
	}
}