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
struct mc33880 {int port_config; } ;

/* Variables and functions */
 int mc33880_write_config (struct mc33880*) ; 

__attribute__((used)) static int __mc33880_set(struct mc33880 *mc, unsigned offset, int value)
{
	if (value)
		mc->port_config |= 1 << offset;
	else
		mc->port_config &= ~(1 << offset);

	return mc33880_write_config(mc);
}