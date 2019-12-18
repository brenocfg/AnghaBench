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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_MAP_LEN_88E ; 
 int /*<<< orphan*/  efuse_ReadEFuse (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efuse_power_switch (struct adapter*,int,int) ; 

__attribute__((used)) static void Efuse_ReadAllMap(struct adapter *pAdapter, u8 efuseType, u8 *Efuse)
{
	efuse_power_switch(pAdapter, false, true);

	efuse_ReadEFuse(pAdapter, efuseType, 0, EFUSE_MAP_LEN_88E, Efuse);

	efuse_power_switch(pAdapter, false, false);
}