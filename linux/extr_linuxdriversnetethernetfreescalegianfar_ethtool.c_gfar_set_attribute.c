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
typedef  int u32 ;
struct filer_table {int dummy; } ;

/* Variables and functions */
#define  RQFCR_PID_DAH 138 
#define  RQFCR_PID_DAL 137 
#define  RQFCR_PID_DPT 136 
#define  RQFCR_PID_ETY 135 
#define  RQFCR_PID_L4P 134 
 int RQFCR_PID_L4P_MASK ; 
 int RQFCR_PID_MAC_MASK ; 
 int RQFCR_PID_PORT_MASK ; 
#define  RQFCR_PID_PRI 133 
 int RQFCR_PID_PRI_MASK ; 
#define  RQFCR_PID_SAH 132 
#define  RQFCR_PID_SAL 131 
#define  RQFCR_PID_SPT 130 
#define  RQFCR_PID_TOS 129 
#define  RQFCR_PID_VID 128 
 int RQFCR_PID_VID_MASK ; 
 int /*<<< orphan*/  gfar_set_general_attribute (int,int,int,struct filer_table*) ; 

__attribute__((used)) static void gfar_set_attribute(u32 value, u32 mask, u32 flag,
			       struct filer_table *tab)
{
	switch (flag) {
		/* 3bit */
	case RQFCR_PID_PRI:
		if (!(value | mask))
			return;
		mask |= RQFCR_PID_PRI_MASK;
		break;
		/* 8bit */
	case RQFCR_PID_L4P:
	case RQFCR_PID_TOS:
		if (!~(mask | RQFCR_PID_L4P_MASK))
			return;
		if (!mask)
			mask = ~0;
		else
			mask |= RQFCR_PID_L4P_MASK;
		break;
		/* 12bit */
	case RQFCR_PID_VID:
		if (!(value | mask))
			return;
		mask |= RQFCR_PID_VID_MASK;
		break;
		/* 16bit */
	case RQFCR_PID_DPT:
	case RQFCR_PID_SPT:
	case RQFCR_PID_ETY:
		if (!~(mask | RQFCR_PID_PORT_MASK))
			return;
		if (!mask)
			mask = ~0;
		else
			mask |= RQFCR_PID_PORT_MASK;
		break;
		/* 24bit */
	case RQFCR_PID_DAH:
	case RQFCR_PID_DAL:
	case RQFCR_PID_SAH:
	case RQFCR_PID_SAL:
		if (!(value | mask))
			return;
		mask |= RQFCR_PID_MAC_MASK;
		break;
		/* for all real 32bit masks */
	default:
		if (!~mask)
			return;
		if (!mask)
			mask = ~0;
		break;
	}
	gfar_set_general_attribute(value, mask, flag, tab);
}