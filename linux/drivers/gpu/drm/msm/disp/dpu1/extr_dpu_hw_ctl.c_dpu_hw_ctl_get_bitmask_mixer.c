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
typedef  int /*<<< orphan*/  uint32_t ;
struct dpu_hw_ctl {int dummy; } ;
typedef  enum dpu_lm { ____Placeholder_dpu_lm } dpu_lm ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CTL_FLUSH_MASK_CTL ; 
 int /*<<< orphan*/  EINVAL ; 
#define  LM_0 133 
#define  LM_1 132 
#define  LM_2 131 
#define  LM_3 130 
#define  LM_4 129 
#define  LM_5 128 

__attribute__((used)) static uint32_t dpu_hw_ctl_get_bitmask_mixer(struct dpu_hw_ctl *ctx,
	enum dpu_lm lm)
{
	uint32_t flushbits = 0;

	switch (lm) {
	case LM_0:
		flushbits = BIT(6);
		break;
	case LM_1:
		flushbits = BIT(7);
		break;
	case LM_2:
		flushbits = BIT(8);
		break;
	case LM_3:
		flushbits = BIT(9);
		break;
	case LM_4:
		flushbits = BIT(10);
		break;
	case LM_5:
		flushbits = BIT(20);
		break;
	default:
		return -EINVAL;
	}

	flushbits |= CTL_FLUSH_MASK_CTL;

	return flushbits;
}