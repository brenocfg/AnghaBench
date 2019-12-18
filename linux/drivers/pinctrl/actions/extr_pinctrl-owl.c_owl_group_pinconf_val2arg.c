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
struct owl_pingroup {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  OWL_PINCONF_DRV_12MA 133 
#define  OWL_PINCONF_DRV_2MA 132 
#define  OWL_PINCONF_DRV_4MA 131 
#define  OWL_PINCONF_DRV_8MA 130 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_SLEW_RATE 128 

__attribute__((used)) static int owl_group_pinconf_val2arg(const struct owl_pingroup *g,
				unsigned int param,
				u32 *arg)
{
	switch (param) {
	case PIN_CONFIG_DRIVE_STRENGTH:
		switch (*arg) {
		case OWL_PINCONF_DRV_2MA:
			*arg = 2;
			break;
		case OWL_PINCONF_DRV_4MA:
			*arg = 4;
			break;
		case OWL_PINCONF_DRV_8MA:
			*arg = 8;
			break;
		case OWL_PINCONF_DRV_12MA:
			*arg = 12;
			break;
		default:
			return -EINVAL;
		}
		break;
	case PIN_CONFIG_SLEW_RATE:
		if (*arg)
			*arg = 1;
		else
			*arg = 0;
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}