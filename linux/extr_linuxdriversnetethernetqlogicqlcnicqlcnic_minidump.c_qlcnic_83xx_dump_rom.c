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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct __mem {int addr; int size; } ;
struct TYPE_2__ {struct __mem mem; } ;
struct qlcnic_dump_entry {TYPE_1__ region; } ;
struct qlcnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  qlcnic_83xx_lockless_flash_read32 (struct qlcnic_adapter*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 qlcnic_83xx_dump_rom(struct qlcnic_adapter *adapter,
				struct qlcnic_dump_entry *entry, __le32 *buffer)
{
	u32 fl_addr, size;
	struct __mem *rom = &entry->region.mem;

	fl_addr = rom->addr;
	size = rom->size / 4;

	if (!qlcnic_83xx_lockless_flash_read32(adapter, fl_addr,
					       (u8 *)buffer, size))
		return rom->size;

	return 0;
}