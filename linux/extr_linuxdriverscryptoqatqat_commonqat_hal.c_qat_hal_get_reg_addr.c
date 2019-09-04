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
 unsigned short BAD_REGADDR ; 
#define  ICP_DR_ABS 143 
#define  ICP_DR_RD_REL 142 
#define  ICP_DR_REL 141 
#define  ICP_DR_WR_REL 140 
#define  ICP_GPA_ABS 139 
#define  ICP_GPA_REL 138 
#define  ICP_GPB_ABS 137 
#define  ICP_GPB_REL 136 
#define  ICP_LMEM0 135 
#define  ICP_LMEM1 134 
#define  ICP_NEIGH_REL 133 
#define  ICP_NO_DEST 132 
#define  ICP_SR_ABS 131 
#define  ICP_SR_RD_REL 130 
#define  ICP_SR_REL 129 
#define  ICP_SR_WR_REL 128 

__attribute__((used)) static unsigned short qat_hal_get_reg_addr(unsigned int type,
					   unsigned short reg_num)
{
	unsigned short reg_addr;

	switch (type) {
	case ICP_GPA_ABS:
	case ICP_GPB_ABS:
		reg_addr = 0x80 | (reg_num & 0x7f);
		break;
	case ICP_GPA_REL:
	case ICP_GPB_REL:
		reg_addr = reg_num & 0x1f;
		break;
	case ICP_SR_RD_REL:
	case ICP_SR_WR_REL:
	case ICP_SR_REL:
		reg_addr = 0x180 | (reg_num & 0x1f);
		break;
	case ICP_SR_ABS:
		reg_addr = 0x140 | ((reg_num & 0x3) << 1);
		break;
	case ICP_DR_RD_REL:
	case ICP_DR_WR_REL:
	case ICP_DR_REL:
		reg_addr = 0x1c0 | (reg_num & 0x1f);
		break;
	case ICP_DR_ABS:
		reg_addr = 0x100 | ((reg_num & 0x3) << 1);
		break;
	case ICP_NEIGH_REL:
		reg_addr = 0x280 | (reg_num & 0x1f);
		break;
	case ICP_LMEM0:
		reg_addr = 0x200;
		break;
	case ICP_LMEM1:
		reg_addr = 0x220;
		break;
	case ICP_NO_DEST:
		reg_addr = 0x300 | (reg_num & 0xff);
		break;
	default:
		reg_addr = BAD_REGADDR;
		break;
	}
	return reg_addr;
}