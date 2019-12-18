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
#define  ALTR_A10SR_FMCAB_REG 137 
#define  ALTR_A10SR_HPS_RST_REG 136 
#define  ALTR_A10SR_LED_REG 135 
#define  ALTR_A10SR_PBDSW_IRQ_REG 134 
#define  ALTR_A10SR_PMBUS_REG 133 
#define  ALTR_A10SR_SFPA_REG 132 
#define  ALTR_A10SR_SFPB_REG 131 
#define  ALTR_A10SR_USB_QSPI_REG 130 
#define  ALTR_A10SR_WARM_RST_REG 129 
#define  ALTR_A10SR_WR_KEY_REG 128 

__attribute__((used)) static bool altr_a10sr_reg_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ALTR_A10SR_LED_REG:
	case ALTR_A10SR_PBDSW_IRQ_REG:
	case ALTR_A10SR_FMCAB_REG:
	case ALTR_A10SR_HPS_RST_REG:
	case ALTR_A10SR_USB_QSPI_REG:
	case ALTR_A10SR_SFPA_REG:
	case ALTR_A10SR_SFPB_REG:
	case ALTR_A10SR_WARM_RST_REG:
	case ALTR_A10SR_WR_KEY_REG:
	case ALTR_A10SR_PMBUS_REG:
		return true;
	default:
		return false;
	}
}