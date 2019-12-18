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
#define  HPC_ALLSLOT_OFF 144 
#define  HPC_ALLSLOT_ON 143 
#define  HPC_BUS_100PCIXMODE 142 
#define  HPC_BUS_133PCIXMODE 141 
#define  HPC_BUS_33CONVMODE 140 
#define  HPC_BUS_66CONVMODE 139 
#define  HPC_BUS_66PCIXMODE 138 
#define  HPC_CTLR_CLEARIRQ 137 
#define  HPC_CTLR_DISABLEIRQ 136 
#define  HPC_CTLR_ENABLEIRQ 135 
#define  HPC_CTLR_IRQSTEER 134 
#define  HPC_CTLR_RESET 133 
 int HPC_ERROR ; 
#define  HPC_SLOT_ATTNOFF 132 
#define  HPC_SLOT_ATTNON 131 
#define  HPC_SLOT_BLINKLED 130 
#define  HPC_SLOT_OFF 129 
#define  HPC_SLOT_ON 128 
 int WPG_1ST_BUS_INDEX ; 
 int /*<<< orphan*/  err (char*,int) ; 

__attribute__((used)) static u8 hpc_writecmdtoindex(u8 cmd, u8 index)
{
	u8 rc;

	switch (cmd) {
	case HPC_CTLR_ENABLEIRQ:	// 0x00.N.15
	case HPC_CTLR_CLEARIRQ:	// 0x06.N.15
	case HPC_CTLR_RESET:	// 0x07.N.15
	case HPC_CTLR_IRQSTEER:	// 0x08.N.15
	case HPC_CTLR_DISABLEIRQ:	// 0x01.N.15
	case HPC_ALLSLOT_ON:	// 0x11.N.15
	case HPC_ALLSLOT_OFF:	// 0x12.N.15
		rc = 0x0F;
		break;

	case HPC_SLOT_OFF:	// 0x02.Y.0-14
	case HPC_SLOT_ON:	// 0x03.Y.0-14
	case HPC_SLOT_ATTNOFF:	// 0x04.N.0-14
	case HPC_SLOT_ATTNON:	// 0x05.N.0-14
	case HPC_SLOT_BLINKLED:	// 0x13.N.0-14
		rc = index;
		break;

	case HPC_BUS_33CONVMODE:
	case HPC_BUS_66CONVMODE:
	case HPC_BUS_66PCIXMODE:
	case HPC_BUS_100PCIXMODE:
	case HPC_BUS_133PCIXMODE:
		rc = index + WPG_1ST_BUS_INDEX - 1;
		break;

	default:
		err("hpc_writecmdtoindex - Error invalid cmd[%x]\n", cmd);
		rc = HPC_ERROR;
	}

	return rc;
}