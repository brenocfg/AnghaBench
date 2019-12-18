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
typedef  size_t u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t FW_8192C_START_ADDRESS ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,size_t,size_t const) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,size_t,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void _rtl88e_fw_block_write(struct adapter *adapt,
				   const u8 *buffer, u32 size)
{
	u32 blk_sz = sizeof(u32);
	const u8 *byte_buffer;
	const u32 *dword_buffer = (u32 *)buffer;
	u32 i, write_address, blk_cnt, remain;

	blk_cnt = size / blk_sz;
	remain = size % blk_sz;

	write_address = FW_8192C_START_ADDRESS;

	for (i = 0; i < blk_cnt; i++, write_address += blk_sz)
		usb_write32(adapt, write_address, dword_buffer[i]);

	byte_buffer = buffer + blk_cnt * blk_sz;
	for (i = 0; i < remain; i++, write_address++)
		usb_write8(adapt, write_address, byte_buffer[i]);
}