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
typedef  int /*<<< orphan*/  u32 ;
struct chelsio_vpd_t {int dummy; } ;
typedef  int /*<<< orphan*/  adapter_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int t1_seeprom_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int t1_eeprom_vpd_get(adapter_t *adapter, struct chelsio_vpd_t *vpd)
{
	int addr, ret = 0;

	for (addr = 0; !ret && addr < sizeof(*vpd); addr += sizeof(u32))
		ret = t1_seeprom_read(adapter, addr,
				      (__le32 *)((u8 *)vpd + addr));

	return ret;
}