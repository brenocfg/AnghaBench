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
#define  APBREG_BSR 134 
 unsigned int APBREG_BSR_SARAC ; 
#define  APBREG_EMU_PCG 133 
#define  APBREG_PAER 132 
#define  APBREG_PCG 131 
#define  APBREG_PRAC 130 
#define  APBREG_PUR 129 
#define  APBREG_PWAC 128 

__attribute__((used)) static bool sta2x11_apbreg_readable_reg(struct device *dev, unsigned int reg)
{
	/* Two blocks (CAN and MLB, SARAC) 0x100 bytes apart */
	if (reg >= APBREG_BSR_SARAC)
		reg -= APBREG_BSR_SARAC;
	switch (reg) {
	case APBREG_BSR:
	case APBREG_PAER:
	case APBREG_PWAC:
	case APBREG_PRAC:
	case APBREG_PCG:
	case APBREG_PUR:
	case APBREG_EMU_PCG:
		return true;
	default:
		return false;
	}
}