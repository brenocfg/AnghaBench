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
struct samsung_pwm_chip {scalar_t__ base; int /*<<< orphan*/  base_clk; } ;

/* Variables and functions */
 scalar_t__ REG_TCFG0 ; 
 int TCFG0_PRESCALER1_SHIFT ; 
 int TCFG0_PRESCALER_MASK ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned long pwm_samsung_get_tin_rate(struct samsung_pwm_chip *chip,
					      unsigned int chan)
{
	unsigned long rate;
	u32 reg;

	rate = clk_get_rate(chip->base_clk);

	reg = readl(chip->base + REG_TCFG0);
	if (chan >= 2)
		reg >>= TCFG0_PRESCALER1_SHIFT;
	reg &= TCFG0_PRESCALER_MASK;

	return rate / (reg + 1);
}