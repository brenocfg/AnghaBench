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
struct device {int dummy; } ;

/* Variables and functions */
#define  STMFX_REG_GPIO_STATE1 145 
#define  STMFX_REG_GPIO_STATE2 144 
#define  STMFX_REG_GPIO_STATE3 143 
#define  STMFX_REG_GPO_CLR1 142 
#define  STMFX_REG_GPO_CLR2 141 
#define  STMFX_REG_GPO_CLR3 140 
#define  STMFX_REG_GPO_SET1 139 
#define  STMFX_REG_GPO_SET2 138 
#define  STMFX_REG_GPO_SET3 137 
#define  STMFX_REG_IRQ_GPI_PENDING1 136 
#define  STMFX_REG_IRQ_GPI_PENDING2 135 
#define  STMFX_REG_IRQ_GPI_PENDING3 134 
#define  STMFX_REG_IRQ_GPI_SRC1 133 
#define  STMFX_REG_IRQ_GPI_SRC2 132 
#define  STMFX_REG_IRQ_GPI_SRC3 131 
#define  STMFX_REG_IRQ_PENDING 130 
#define  STMFX_REG_IRQ_SRC_EN 129 
#define  STMFX_REG_SYS_CTRL 128 

__attribute__((used)) static bool stmfx_reg_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case STMFX_REG_SYS_CTRL:
	case STMFX_REG_IRQ_SRC_EN:
	case STMFX_REG_IRQ_PENDING:
	case STMFX_REG_IRQ_GPI_PENDING1:
	case STMFX_REG_IRQ_GPI_PENDING2:
	case STMFX_REG_IRQ_GPI_PENDING3:
	case STMFX_REG_GPIO_STATE1:
	case STMFX_REG_GPIO_STATE2:
	case STMFX_REG_GPIO_STATE3:
	case STMFX_REG_IRQ_GPI_SRC1:
	case STMFX_REG_IRQ_GPI_SRC2:
	case STMFX_REG_IRQ_GPI_SRC3:
	case STMFX_REG_GPO_SET1:
	case STMFX_REG_GPO_SET2:
	case STMFX_REG_GPO_SET3:
	case STMFX_REG_GPO_CLR1:
	case STMFX_REG_GPO_CLR2:
	case STMFX_REG_GPO_CLR3:
		return true;
	default:
		return false;
	}
}