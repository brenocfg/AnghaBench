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
 int BCM590XX_CSRPMCTRL1 ; 
 int BCM590XX_GPLDO1PMCTRL1 ; 
 int BCM590XX_IOSR1PMCTRL1 ; 
 int BCM590XX_IOSR2PMCTRL1 ; 
 int BCM590XX_MSRPMCTRL1 ; 
 int BCM590XX_OTG_CTRL ; 
#define  BCM590XX_REG_CSR 135 
#define  BCM590XX_REG_IOSR1 134 
#define  BCM590XX_REG_IOSR2 133 
 scalar_t__ BCM590XX_REG_IS_GPLDO (int) ; 
 scalar_t__ BCM590XX_REG_IS_LDO (int) ; 
#define  BCM590XX_REG_MSR 132 
#define  BCM590XX_REG_SDSR1 131 
#define  BCM590XX_REG_SDSR2 130 
#define  BCM590XX_REG_VBUS 129 
#define  BCM590XX_REG_VSR 128 
 int BCM590XX_RFLDOPMCTRL1 ; 
 int BCM590XX_SDSR1PMCTRL1 ; 
 int BCM590XX_SDSR2PMCTRL1 ; 
 int BCM590XX_VSRPMCTRL1 ; 

__attribute__((used)) static int bcm590xx_get_enable_register(int id)
{
	int reg = 0;

	if (BCM590XX_REG_IS_LDO(id))
		reg = BCM590XX_RFLDOPMCTRL1 + id * 2;
	else if (BCM590XX_REG_IS_GPLDO(id))
		reg = BCM590XX_GPLDO1PMCTRL1 + id * 2;
	else
		switch (id) {
		case BCM590XX_REG_CSR:
			reg = BCM590XX_CSRPMCTRL1;
			break;
		case BCM590XX_REG_IOSR1:
			reg = BCM590XX_IOSR1PMCTRL1;
			break;
		case BCM590XX_REG_IOSR2:
			reg = BCM590XX_IOSR2PMCTRL1;
			break;
		case BCM590XX_REG_MSR:
			reg = BCM590XX_MSRPMCTRL1;
			break;
		case BCM590XX_REG_SDSR1:
			reg = BCM590XX_SDSR1PMCTRL1;
			break;
		case BCM590XX_REG_SDSR2:
			reg = BCM590XX_SDSR2PMCTRL1;
			break;
		case BCM590XX_REG_VSR:
			reg = BCM590XX_VSRPMCTRL1;
			break;
		case BCM590XX_REG_VBUS:
			reg = BCM590XX_OTG_CTRL;
			break;
		}


	return reg;
}