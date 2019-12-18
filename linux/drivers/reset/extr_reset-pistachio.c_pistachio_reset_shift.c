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
 int EINVAL ; 
#define  PISTACHIO_RESET_ETHERNET 152 
#define  PISTACHIO_RESET_EVT 151 
#define  PISTACHIO_RESET_HASH 150 
#define  PISTACHIO_RESET_I2C0 149 
#define  PISTACHIO_RESET_I2C1 148 
#define  PISTACHIO_RESET_I2C2 147 
#define  PISTACHIO_RESET_I2C3 146 
#define  PISTACHIO_RESET_I2S_IN 145 
#define  PISTACHIO_RESET_I2S_OUT 144 
#define  PISTACHIO_RESET_IR 143 
#define  PISTACHIO_RESET_MDC 142 
#define  PISTACHIO_RESET_PRL_OUT 141 
#define  PISTACHIO_RESET_PWM_PDM 140 
#define  PISTACHIO_RESET_QSPI 139 
#define  PISTACHIO_RESET_SDHOST 138 
#define  PISTACHIO_RESET_SPDIF_IN 137 
#define  PISTACHIO_RESET_SPDIF_OUT 136 
#define  PISTACHIO_RESET_SPI 135 
#define  PISTACHIO_RESET_TIMER 134 
#define  PISTACHIO_RESET_UART0 133 
#define  PISTACHIO_RESET_UART1 132 
#define  PISTACHIO_RESET_USB_H 131 
#define  PISTACHIO_RESET_USB_PHY_PON 130 
#define  PISTACHIO_RESET_USB_PHY_PR 129 
#define  PISTACHIO_RESET_USB_PR 128 

__attribute__((used)) static inline int pistachio_reset_shift(unsigned long id)
{
	switch (id) {
	case PISTACHIO_RESET_I2C0:
	case PISTACHIO_RESET_I2C1:
	case PISTACHIO_RESET_I2C2:
	case PISTACHIO_RESET_I2C3:
	case PISTACHIO_RESET_I2S_IN:
	case PISTACHIO_RESET_PRL_OUT:
	case PISTACHIO_RESET_SPDIF_OUT:
	case PISTACHIO_RESET_SPI:
	case PISTACHIO_RESET_PWM_PDM:
	case PISTACHIO_RESET_UART0:
	case PISTACHIO_RESET_UART1:
	case PISTACHIO_RESET_QSPI:
	case PISTACHIO_RESET_MDC:
	case PISTACHIO_RESET_SDHOST:
	case PISTACHIO_RESET_ETHERNET:
	case PISTACHIO_RESET_IR:
	case PISTACHIO_RESET_HASH:
	case PISTACHIO_RESET_TIMER:
		return id;
	case PISTACHIO_RESET_I2S_OUT:
	case PISTACHIO_RESET_SPDIF_IN:
	case PISTACHIO_RESET_EVT:
		return id + 6;
	case PISTACHIO_RESET_USB_H:
	case PISTACHIO_RESET_USB_PR:
	case PISTACHIO_RESET_USB_PHY_PR:
	case PISTACHIO_RESET_USB_PHY_PON:
		return id + 7;
	default:
		return -EINVAL;
	}
}