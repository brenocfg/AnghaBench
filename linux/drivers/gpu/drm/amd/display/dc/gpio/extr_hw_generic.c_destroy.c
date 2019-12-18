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
struct hw_gpio_pin {int dummy; } ;
struct hw_generic {int dummy; } ;

/* Variables and functions */
 struct hw_generic* HW_GENERIC_FROM_BASE (struct hw_gpio_pin*) ; 
 int /*<<< orphan*/  dal_hw_generic_destruct (struct hw_generic*) ; 
 int /*<<< orphan*/  kfree (struct hw_generic*) ; 

__attribute__((used)) static void destroy(
	struct hw_gpio_pin **ptr)
{
	struct hw_generic *generic = HW_GENERIC_FROM_BASE(*ptr);

	dal_hw_generic_destruct(generic);

	kfree(generic);

	*ptr = NULL;
}