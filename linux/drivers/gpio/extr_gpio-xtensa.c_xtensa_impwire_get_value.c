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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  disable_cp (unsigned long,unsigned long) ; 
 unsigned long enable_cp (unsigned long*) ; 

__attribute__((used)) static int xtensa_impwire_get_value(struct gpio_chip *gc, unsigned offset)
{
	unsigned long flags, saved_cpenable;
	u32 impwire;

	flags = enable_cp(&saved_cpenable);
	__asm__ __volatile__("read_impwire %0" : "=a" (impwire));
	disable_cp(flags, saved_cpenable);

	return !!(impwire & BIT(offset));
}