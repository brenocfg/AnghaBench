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
struct analogix_dp_device {scalar_t__ reg_base; } ;
typedef  enum pattern_set { ____Placeholder_pattern_set } pattern_set ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_TRAINING_PTN_SET ; 
#define  D10_2 132 
#define  DP_NONE 131 
 int LINK_QUAL_PATTERN_SET_D10_2 ; 
 int LINK_QUAL_PATTERN_SET_DISABLE ; 
 int LINK_QUAL_PATTERN_SET_PRBS7 ; 
#define  PRBS7 130 
 int SCRAMBLING_DISABLE ; 
 int SCRAMBLING_ENABLE ; 
 int SW_TRAINING_PATTERN_SET_NORMAL ; 
 int SW_TRAINING_PATTERN_SET_PTN1 ; 
 int SW_TRAINING_PATTERN_SET_PTN2 ; 
#define  TRAINING_PTN1 129 
#define  TRAINING_PTN2 128 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_set_training_pattern(struct analogix_dp_device *dp,
				      enum pattern_set pattern)
{
	u32 reg;

	switch (pattern) {
	case PRBS7:
		reg = SCRAMBLING_ENABLE | LINK_QUAL_PATTERN_SET_PRBS7;
		writel(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		break;
	case D10_2:
		reg = SCRAMBLING_ENABLE | LINK_QUAL_PATTERN_SET_D10_2;
		writel(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		break;
	case TRAINING_PTN1:
		reg = SCRAMBLING_DISABLE | SW_TRAINING_PATTERN_SET_PTN1;
		writel(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		break;
	case TRAINING_PTN2:
		reg = SCRAMBLING_DISABLE | SW_TRAINING_PATTERN_SET_PTN2;
		writel(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		break;
	case DP_NONE:
		reg = SCRAMBLING_ENABLE |
			LINK_QUAL_PATTERN_SET_DISABLE |
			SW_TRAINING_PATTERN_SET_NORMAL;
		writel(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		break;
	default:
		break;
	}
}