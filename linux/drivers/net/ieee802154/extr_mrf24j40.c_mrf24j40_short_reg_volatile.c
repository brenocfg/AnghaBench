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
#define  REG_BBREG1 143 
#define  REG_BBREG6 142 
#define  REG_INTSTAT 141 
#define  REG_RFCTL 140 
#define  REG_RXFLUSH 139 
#define  REG_RXSR 138 
#define  REG_SECCON0 137 
#define  REG_SECCR2 136 
#define  REG_SLPACK 135 
#define  REG_SOFTRST 134 
#define  REG_TXBCON0 133 
#define  REG_TXBCON1 132 
#define  REG_TXG1CON 131 
#define  REG_TXG2CON 130 
#define  REG_TXNCON 129 
#define  REG_TXSTAT 128 

__attribute__((used)) static bool
mrf24j40_short_reg_volatile(struct device *dev, unsigned int reg)
{
	/* can be changed during runtime */
	switch (reg) {
	case REG_TXSTAT:
	case REG_INTSTAT:
	case REG_RXFLUSH:
	case REG_TXNCON:
	case REG_SOFTRST:
	case REG_RFCTL:
	case REG_TXBCON0:
	case REG_TXG1CON:
	case REG_TXG2CON:
	case REG_TXBCON1:
	case REG_SECCON0:
	case REG_RXSR:
	case REG_SLPACK:
	case REG_SECCR2:
	case REG_BBREG6:
	/* use them in spi_async and regmap so it's volatile */
	case REG_BBREG1:
		return true;
	default:
		return false;
	}
}