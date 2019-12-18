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
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ apbmisc_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

u32 tegra_read_chipid(void)
{
	if (!apbmisc_base) {
		WARN(1, "Tegra Chip ID not yet available\n");
		return 0;
	}

	return readl_relaxed(apbmisc_base + 4);
}