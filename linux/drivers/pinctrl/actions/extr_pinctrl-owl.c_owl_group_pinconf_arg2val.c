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
typedef  int /*<<< orphan*/  u32 ;
struct owl_pingroup {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  OWL_PINCONF_DRV_12MA ; 
 int /*<<< orphan*/  OWL_PINCONF_DRV_2MA ; 
 int /*<<< orphan*/  OWL_PINCONF_DRV_4MA ; 
 int /*<<< orphan*/  OWL_PINCONF_DRV_8MA ; 
 int /*<<< orphan*/  OWL_PINCONF_SLEW_FAST ; 
 int /*<<< orphan*/  OWL_PINCONF_SLEW_SLOW ; 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_SLEW_RATE 128 

__attribute__((used)) static int owl_group_pinconf_arg2val(const struct owl_pingroup *g,
				unsigned int param,
				u32 *arg)
{
	switch (param) {
	case PIN_CONFIG_DRIVE_STRENGTH:
		switch (*arg) {
		case 2:
			*arg = OWL_PINCONF_DRV_2MA;
			break;
		case 4:
			*arg = OWL_PINCONF_DRV_4MA;
			break;
		case 8:
			*arg = OWL_PINCONF_DRV_8MA;
			break;
		case 12:
			*arg = OWL_PINCONF_DRV_12MA;
			break;
		default:
			return -EINVAL;
		}
		break;
	case PIN_CONFIG_SLEW_RATE:
		if (*arg)
			*arg = OWL_PINCONF_SLEW_FAST;
		else
			*arg = OWL_PINCONF_SLEW_SLOW;
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}