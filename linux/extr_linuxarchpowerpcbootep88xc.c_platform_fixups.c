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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PLANETCORE_KEY_CRYSTAL_HZ ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_size ; 
 int /*<<< orphan*/  mpc885_fixup_clocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  planetcore_get_decimal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  planetcore_set_mac_addrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  table ; 

__attribute__((used)) static void platform_fixups(void)
{
	u64 val;

	dt_fixup_memory(0, mem_size);
	planetcore_set_mac_addrs(table);

	if (!planetcore_get_decimal(table, PLANETCORE_KEY_CRYSTAL_HZ, &val)) {
		printf("No PlanetCore crystal frequency key.\r\n");
		return;
	}

	mpc885_fixup_clocks(val);
}