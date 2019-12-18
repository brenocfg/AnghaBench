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
struct rtw_efuse {int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct rtw8822c_efuse {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822ce_efuse_parsing(struct rtw_efuse *efuse,
				    struct rtw8822c_efuse *map)
{
	ether_addr_copy(efuse->addr, map->e.mac_addr);
}