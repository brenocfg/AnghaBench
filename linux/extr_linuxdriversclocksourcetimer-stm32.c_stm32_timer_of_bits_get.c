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
struct timer_of {struct stm32_timer_private* private_data; } ;
struct stm32_timer_private {int bits; } ;

/* Variables and functions */

__attribute__((used)) static int stm32_timer_of_bits_get(struct timer_of *to)
{
	struct stm32_timer_private *pd = to->private_data;

	return pd->bits;
}