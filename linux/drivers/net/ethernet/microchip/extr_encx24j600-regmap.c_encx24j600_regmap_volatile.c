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
#define  ECON1 137 
#define  ECON2 136 
#define  EDMACS 135 
#define  EIR 134 
#define  ERXHEAD 133 
#define  ESTAT 132 
#define  ETXSTAT 131 
#define  ETXWIRE 130 
#define  MIRD 129 
#define  MISTAT 128 

__attribute__((used)) static bool encx24j600_regmap_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ERXHEAD:
	case EDMACS:
	case ETXSTAT:
	case ETXWIRE:
	case ECON1:	/* Can be modified via single byte cmds */
	case ECON2:	/* Can be modified via single byte cmds */
	case ESTAT:
	case EIR:	/* Can be modified via single byte cmds */
	case MIRD:
	case MISTAT:
		return true;
	default:
		break;
	}

	return false;
}