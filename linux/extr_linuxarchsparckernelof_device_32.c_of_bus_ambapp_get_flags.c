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

/* Variables and functions */
 unsigned long IORESOURCE_MEM ; 

__attribute__((used)) static unsigned long of_bus_ambapp_get_flags(const u32 *addr,
					     unsigned long flags)
{
	return IORESOURCE_MEM;
}