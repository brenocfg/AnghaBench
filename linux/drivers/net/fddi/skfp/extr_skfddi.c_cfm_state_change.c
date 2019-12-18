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
struct s_smc {int dummy; } ;

/* Variables and functions */
#define  SC0_ISOLATED 136 
#define  SC10_C_WRAP_B 135 
#define  SC11_C_WRAP_S 134 
#define  SC1_WRAP_A 133 
#define  SC2_WRAP_B 132 
#define  SC4_THRU_A 131 
#define  SC5_THRU_B 130 
#define  SC7_WRAP_S 129 
#define  SC9_C_WRAP_A 128 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

void cfm_state_change(struct s_smc *smc, int c_state)
{
#ifdef DRIVERDEBUG
	char *s;

	switch (c_state) {
	case SC0_ISOLATED:
		s = "SC0_ISOLATED";
		break;
	case SC1_WRAP_A:
		s = "SC1_WRAP_A";
		break;
	case SC2_WRAP_B:
		s = "SC2_WRAP_B";
		break;
	case SC4_THRU_A:
		s = "SC4_THRU_A";
		break;
	case SC5_THRU_B:
		s = "SC5_THRU_B";
		break;
	case SC7_WRAP_S:
		s = "SC7_WRAP_S";
		break;
	case SC9_C_WRAP_A:
		s = "SC9_C_WRAP_A";
		break;
	case SC10_C_WRAP_B:
		s = "SC10_C_WRAP_B";
		break;
	case SC11_C_WRAP_S:
		s = "SC11_C_WRAP_S";
		break;
	default:
		pr_debug("cfm_state_change: unknown %d\n", c_state);
		return;
	}
	pr_debug("cfm_state_change: %s\n", s);
#endif				// DRIVERDEBUG
}