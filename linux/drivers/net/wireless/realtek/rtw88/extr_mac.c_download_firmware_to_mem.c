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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {scalar_t__ tx_pkt_desc_sz; } ;

/* Variables and functions */
 scalar_t__ BIT_DDMACH0_RESET_CHKSUM_STS ; 
 int EINVAL ; 
 scalar_t__ OCPBASE_TXBUF_88XX ; 
 int /*<<< orphan*/  REG_DDMA_CH0CTRL ; 
 int /*<<< orphan*/  check_fw_checksum (struct rtw_dev*,scalar_t__) ; 
 int iddma_download_firmware (struct rtw_dev*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int send_firmware_pkt (struct rtw_dev*,int /*<<< orphan*/ ,int const*,scalar_t__) ; 

__attribute__((used)) static int
download_firmware_to_mem(struct rtw_dev *rtwdev, const u8 *data,
			 u32 src, u32 dst, u32 size)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	u32 desc_size = chip->tx_pkt_desc_sz;
	u8 first_part;
	u32 mem_offset;
	u32 residue_size;
	u32 pkt_size;
	u32 max_size = 0x1000;
	u32 val;
	int ret;

	mem_offset = 0;
	first_part = 1;
	residue_size = size;

	val = rtw_read32(rtwdev, REG_DDMA_CH0CTRL);
	val |= BIT_DDMACH0_RESET_CHKSUM_STS;
	rtw_write32(rtwdev, REG_DDMA_CH0CTRL, val);

	while (residue_size) {
		if (residue_size >= max_size)
			pkt_size = max_size;
		else
			pkt_size = residue_size;

		ret = send_firmware_pkt(rtwdev, (u16)(src >> 7),
					data + mem_offset, pkt_size);
		if (ret)
			return ret;

		ret = iddma_download_firmware(rtwdev, OCPBASE_TXBUF_88XX +
					      src + desc_size,
					      dst + mem_offset, pkt_size,
					      first_part);
		if (ret)
			return ret;

		first_part = 0;
		mem_offset += pkt_size;
		residue_size -= pkt_size;
	}

	if (!check_fw_checksum(rtwdev, dst))
		return -EINVAL;

	return 0;
}