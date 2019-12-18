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
struct tc_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  refclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int LSCLK_DIV_2 ; 
 int REF_FREQ_13M ; 
 int REF_FREQ_19M2 ; 
 int REF_FREQ_26M ; 
 int REF_FREQ_38M4 ; 
 int SYSCLK_SEL_LSCLK ; 
 int /*<<< orphan*/  SYS_PLLPARAM ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc_set_syspllparam(struct tc_data *tc)
{
	unsigned long rate;
	u32 pllparam = SYSCLK_SEL_LSCLK | LSCLK_DIV_2;

	rate = clk_get_rate(tc->refclk);
	switch (rate) {
	case 38400000:
		pllparam |= REF_FREQ_38M4;
		break;
	case 26000000:
		pllparam |= REF_FREQ_26M;
		break;
	case 19200000:
		pllparam |= REF_FREQ_19M2;
		break;
	case 13000000:
		pllparam |= REF_FREQ_13M;
		break;
	default:
		dev_err(tc->dev, "Invalid refclk rate: %lu Hz\n", rate);
		return -EINVAL;
	}

	return regmap_write(tc->regmap, SYS_PLLPARAM, pllparam);
}