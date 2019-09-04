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
struct omap2_onenand {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ONENAND_REG_SYS_CFG1 ; 
 unsigned short ONENAND_SYS_CFG1_BL_16 ; 
 unsigned short ONENAND_SYS_CFG1_BL_32 ; 
 unsigned short ONENAND_SYS_CFG1_BL_4 ; 
 unsigned short ONENAND_SYS_CFG1_BL_8 ; 
 int ONENAND_SYS_CFG1_BRL_SHIFT ; 
 unsigned short ONENAND_SYS_CFG1_HF ; 
 unsigned short ONENAND_SYS_CFG1_INT ; 
 unsigned short ONENAND_SYS_CFG1_RDY ; 
 unsigned short ONENAND_SYS_CFG1_SYNC_READ ; 
 unsigned short ONENAND_SYS_CFG1_SYNC_WRITE ; 
 unsigned short ONENAND_SYS_CFG1_VHF ; 
 int /*<<< orphan*/  write_reg (struct omap2_onenand*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_onenand_set_cfg(struct omap2_onenand *c,
				 bool sr, bool sw,
				 int latency, int burst_len)
{
	unsigned short reg = ONENAND_SYS_CFG1_RDY | ONENAND_SYS_CFG1_INT;

	reg |= latency << ONENAND_SYS_CFG1_BRL_SHIFT;

	switch (burst_len) {
	case 0:		/* continuous */
		break;
	case 4:
		reg |= ONENAND_SYS_CFG1_BL_4;
		break;
	case 8:
		reg |= ONENAND_SYS_CFG1_BL_8;
		break;
	case 16:
		reg |= ONENAND_SYS_CFG1_BL_16;
		break;
	case 32:
		reg |= ONENAND_SYS_CFG1_BL_32;
		break;
	default:
		return -EINVAL;
	}

	if (latency > 5)
		reg |= ONENAND_SYS_CFG1_HF;
	if (latency > 7)
		reg |= ONENAND_SYS_CFG1_VHF;
	if (sr)
		reg |= ONENAND_SYS_CFG1_SYNC_READ;
	if (sw)
		reg |= ONENAND_SYS_CFG1_SYNC_WRITE;

	write_reg(c, reg, ONENAND_REG_SYS_CFG1);

	return 0;
}