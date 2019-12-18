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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gw_pld_output8 (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static void gw_pld_set8(struct gpio_chip *gc, unsigned offset, int value)
{
	gw_pld_output8(gc, offset, value);
}