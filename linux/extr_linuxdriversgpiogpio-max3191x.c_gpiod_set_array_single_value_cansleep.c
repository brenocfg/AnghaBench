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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (unsigned int,struct gpio_desc**,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpiod_set_array_single_value_cansleep(unsigned int ndescs,
						  struct gpio_desc **desc,
						  int value)
{
	int i, *values;

	values = kmalloc_array(ndescs, sizeof(*values), GFP_KERNEL);
	if (!values)
		return;

	for (i = 0; i < ndescs; i++)
		values[i] = value;

	gpiod_set_array_value_cansleep(ndescs, desc, values);
	kfree(values);
}