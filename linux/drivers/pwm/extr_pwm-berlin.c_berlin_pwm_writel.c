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
struct berlin_pwm_chip {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void berlin_pwm_writel(struct berlin_pwm_chip *chip,
				     unsigned int channel, u32 value,
				     unsigned long offset)
{
	writel_relaxed(value, chip->base + channel * 0x10 + offset);
}