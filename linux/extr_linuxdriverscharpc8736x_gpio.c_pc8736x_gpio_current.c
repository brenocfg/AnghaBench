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

/* Variables and functions */
 int* pc8736x_gpio_shadow ; 

__attribute__((used)) static int pc8736x_gpio_current(unsigned minor)
{
	int port, bit;
	minor &= 0x1f;
	port = minor >> 3;
	bit = minor & 7;
	return ((pc8736x_gpio_shadow[port] >> bit) & 0x01);
}