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
struct stm32_pwm {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIM_CCR1 ; 
 int /*<<< orphan*/  TIM_CCR2 ; 
 int /*<<< orphan*/  TIM_CCR3 ; 
 int /*<<< orphan*/  TIM_CCR4 ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_ccrx(struct stm32_pwm *dev, int ch, u32 value)
{
	switch (ch) {
	case 0:
		return regmap_write(dev->regmap, TIM_CCR1, value);
	case 1:
		return regmap_write(dev->regmap, TIM_CCR2, value);
	case 2:
		return regmap_write(dev->regmap, TIM_CCR3, value);
	case 3:
		return regmap_write(dev->regmap, TIM_CCR4, value);
	}
	return -EINVAL;
}