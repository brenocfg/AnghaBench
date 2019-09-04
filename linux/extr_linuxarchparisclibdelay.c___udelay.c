#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cpu_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cr16_delay (unsigned long) ; 
 TYPE_1__ boot_cpu_data ; 

void __udelay(unsigned long usecs)
{
	__cr16_delay(usecs * ((unsigned long)boot_cpu_data.cpu_hz / 1000000UL));
}