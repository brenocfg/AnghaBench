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
 int HPC_ERROR ; 
#define  READ_ALLSTAT 135 
#define  READ_BUSSTATUS 134 
#define  READ_CTLRSTATUS 133 
#define  READ_EXTSLOTSTATUS 132 
#define  READ_HPCOPTIONS 131 
#define  READ_REVLEVEL 130 
#define  READ_SLOTLATCHLOWREG 129 
#define  READ_SLOTSTATUS 128 
 int WPG_1ST_BUS_INDEX ; 
 int WPG_1ST_EXTSLOT_INDEX ; 

__attribute__((used)) static u8 hpc_readcmdtoindex(u8 cmd, u8 index)
{
	u8 rc;

	switch (cmd) {
	case READ_CTLRSTATUS:
		rc = 0x0F;
		break;
	case READ_SLOTSTATUS:
	case READ_ALLSTAT:
		rc = index;
		break;
	case READ_EXTSLOTSTATUS:
		rc = index + WPG_1ST_EXTSLOT_INDEX;
		break;
	case READ_BUSSTATUS:
		rc = index + WPG_1ST_BUS_INDEX - 1;
		break;
	case READ_SLOTLATCHLOWREG:
		rc = 0x28;
		break;
	case READ_REVLEVEL:
		rc = 0x25;
		break;
	case READ_HPCOPTIONS:
		rc = 0x27;
		break;
	default:
		rc = HPC_ERROR;
	}
	return rc;
}