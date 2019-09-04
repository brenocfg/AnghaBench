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
struct qlcnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int do_rom_fast_read (struct qlcnic_adapter*,int,int*) ; 

__attribute__((used)) static int do_rom_fast_read_words(struct qlcnic_adapter *adapter, int addr,
				  u8 *bytes, size_t size)
{
	int addridx;
	int ret = 0;

	for (addridx = addr; addridx < (addr + size); addridx += 4) {
		int v;
		ret = do_rom_fast_read(adapter, addridx, &v);
		if (ret != 0)
			break;
		*(__le32 *)bytes = cpu_to_le32(v);
		bytes += 4;
	}

	return ret;
}