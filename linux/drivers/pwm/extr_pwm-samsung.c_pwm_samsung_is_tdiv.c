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
struct samsung_pwm_variant {int tclk_mask; } ;
struct samsung_pwm_chip {scalar_t__ base; struct samsung_pwm_variant variant; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ REG_TCFG1 ; 
 int TCFG1_MUX_MASK ; 
 int TCFG1_SHIFT (unsigned int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int pwm_samsung_is_tdiv(struct samsung_pwm_chip *chip, unsigned int chan)
{
	struct samsung_pwm_variant *variant = &chip->variant;
	u32 reg;

	reg = readl(chip->base + REG_TCFG1);
	reg >>= TCFG1_SHIFT(chan);
	reg &= TCFG1_MUX_MASK;

	return (BIT(reg) & variant->tclk_mask) == 0;
}