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
typedef  int uint ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS8841_WOL_FRAME_BYTE0_OFFSET ; 
 scalar_t__ KS8841_WOL_FRAME_BYTE2_OFFSET ; 
 scalar_t__ KS8841_WOL_FRAME_CRC_OFFSET ; 
 int /*<<< orphan*/  ether_crc (int,int*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_set_wol_frame(struct ksz_hw *hw, int i, uint mask_size,
	const u8 *mask, uint frame_size, const u8 *pattern)
{
	int bits;
	int from;
	int len;
	int to;
	u32 crc;
	u8 data[64];
	u8 val = 0;

	if (frame_size > mask_size * 8)
		frame_size = mask_size * 8;
	if (frame_size > 64)
		frame_size = 64;

	i *= 0x10;
	writel(0, hw->io + KS8841_WOL_FRAME_BYTE0_OFFSET + i);
	writel(0, hw->io + KS8841_WOL_FRAME_BYTE2_OFFSET + i);

	bits = len = from = to = 0;
	do {
		if (bits) {
			if ((val & 1))
				data[to++] = pattern[from];
			val >>= 1;
			++from;
			--bits;
		} else {
			val = mask[len];
			writeb(val, hw->io + KS8841_WOL_FRAME_BYTE0_OFFSET + i
				+ len);
			++len;
			if (val)
				bits = 8;
			else
				from += 8;
		}
	} while (from < (int) frame_size);
	if (val) {
		bits = mask[len - 1];
		val <<= (from % 8);
		bits &= ~val;
		writeb(bits, hw->io + KS8841_WOL_FRAME_BYTE0_OFFSET + i + len -
			1);
	}
	crc = ether_crc(to, data);
	writel(crc, hw->io + KS8841_WOL_FRAME_CRC_OFFSET + i);
}