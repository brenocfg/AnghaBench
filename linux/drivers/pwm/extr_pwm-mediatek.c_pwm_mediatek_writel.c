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
struct pwm_mediatek_chip {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__* pwm_mediatek_reg_offset ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void pwm_mediatek_writel(struct pwm_mediatek_chip *chip,
				       unsigned int num, unsigned int offset,
				       u32 value)
{
	writel(value, chip->regs + pwm_mediatek_reg_offset[num] + offset);
}