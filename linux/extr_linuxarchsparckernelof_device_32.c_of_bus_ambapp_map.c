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
 int of_bus_default_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static int of_bus_ambapp_map(u32 *addr, const u32 *range,
			     int na, int ns, int pna)
{
	return of_bus_default_map(addr, range, na, ns, pna);
}