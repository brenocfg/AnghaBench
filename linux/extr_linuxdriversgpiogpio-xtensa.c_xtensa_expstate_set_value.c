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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  disable_cp (unsigned long,unsigned long) ; 
 unsigned long enable_cp (unsigned long*) ; 

__attribute__((used)) static void xtensa_expstate_set_value(struct gpio_chip *gc, unsigned offset,
				     int value)
{
	unsigned long flags, saved_cpenable;
	u32 mask = BIT(offset);
	u32 val = value ? BIT(offset) : 0;

	flags = enable_cp(&saved_cpenable);
	__asm__ __volatile__("wrmsk_expstate %0, %1"
			     :: "a" (val), "a" (mask));
	disable_cp(flags, saved_cpenable);
}