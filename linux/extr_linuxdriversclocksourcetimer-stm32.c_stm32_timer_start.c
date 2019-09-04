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
struct timer_of {int dummy; } ;

/* Variables and functions */
 scalar_t__ TIM_CR1 ; 
 int TIM_CR1_CEN ; 
 int TIM_CR1_UDIS ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32_timer_start(struct timer_of *to)
{
	writel_relaxed(TIM_CR1_UDIS | TIM_CR1_CEN, timer_of_base(to) + TIM_CR1);
}