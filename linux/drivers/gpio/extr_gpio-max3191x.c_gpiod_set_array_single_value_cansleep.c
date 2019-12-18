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
struct gpio_desc {int dummy; } ;
struct gpio_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long* bitmap_alloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_fill (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (unsigned int,struct gpio_desc**,struct gpio_array*,unsigned long*) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 

__attribute__((used)) static void gpiod_set_array_single_value_cansleep(unsigned int ndescs,
						  struct gpio_desc **desc,
						  struct gpio_array *info,
						  int value)
{
	unsigned long *values;

	values = bitmap_alloc(ndescs, GFP_KERNEL);
	if (!values)
		return;

	if (value)
		bitmap_fill(values, ndescs);
	else
		bitmap_zero(values, ndescs);

	gpiod_set_array_value_cansleep(ndescs, desc, info, values);
	kfree(values);
}