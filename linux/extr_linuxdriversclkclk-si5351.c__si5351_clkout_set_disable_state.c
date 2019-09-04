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
typedef  int u8 ;
struct si5351_driver_data {int dummy; } ;
typedef  enum si5351_disable_state { ____Placeholder_si5351_disable_state } si5351_disable_state ;

/* Variables and functions */
 int EINVAL ; 
 int SI5351_CLK3_0_DISABLE_STATE ; 
 int SI5351_CLK7_4_DISABLE_STATE ; 
 int SI5351_CLK_DISABLE_STATE_FLOAT ; 
 int SI5351_CLK_DISABLE_STATE_HIGH ; 
 int SI5351_CLK_DISABLE_STATE_LOW ; 
 int SI5351_CLK_DISABLE_STATE_MASK ; 
 int SI5351_CLK_DISABLE_STATE_NEVER ; 
#define  SI5351_DISABLE_FLOATING 131 
#define  SI5351_DISABLE_HIGH 130 
#define  SI5351_DISABLE_LOW 129 
#define  SI5351_DISABLE_NEVER 128 
 int /*<<< orphan*/  si5351_set_bits (struct si5351_driver_data*,int,int,int) ; 

__attribute__((used)) static int _si5351_clkout_set_disable_state(
	struct si5351_driver_data *drvdata, int num,
	enum si5351_disable_state state)
{
	u8 reg = (num < 4) ? SI5351_CLK3_0_DISABLE_STATE :
		SI5351_CLK7_4_DISABLE_STATE;
	u8 shift = (num < 4) ? (2 * num) : (2 * (num-4));
	u8 mask = SI5351_CLK_DISABLE_STATE_MASK << shift;
	u8 val;

	if (num > 8)
		return -EINVAL;

	switch (state) {
	case SI5351_DISABLE_LOW:
		val = SI5351_CLK_DISABLE_STATE_LOW;
		break;
	case SI5351_DISABLE_HIGH:
		val = SI5351_CLK_DISABLE_STATE_HIGH;
		break;
	case SI5351_DISABLE_FLOATING:
		val = SI5351_CLK_DISABLE_STATE_FLOAT;
		break;
	case SI5351_DISABLE_NEVER:
		val = SI5351_CLK_DISABLE_STATE_NEVER;
		break;
	default:
		return 0;
	}

	si5351_set_bits(drvdata, reg, mask, val << shift);

	return 0;
}