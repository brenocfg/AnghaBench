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
typedef  int u32 ;
struct rtw_fifo_conf {int rsvd_h2cq_addr; } ;
struct rtw_dev {struct rtw_fifo_conf fifo; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_H2C_HEAD ; 
 scalar_t__ REG_H2C_INFO ; 
 int /*<<< orphan*/  REG_H2C_PKT_READADDR ; 
 int /*<<< orphan*/  REG_H2C_PKT_WRITEADDR ; 
 int /*<<< orphan*/  REG_H2C_READ_ADDR ; 
 int /*<<< orphan*/  REG_H2C_TAIL ; 
 scalar_t__ REG_TXDMA_OFFSET_CHK ; 
 int RSVD_PG_H2CQ_NUM ; 
 int TX_PAGE_SIZE_SHIFT ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int) ; 

__attribute__((used)) static int init_h2c(struct rtw_dev *rtwdev)
{
	struct rtw_fifo_conf *fifo = &rtwdev->fifo;
	u8 value8;
	u32 value32;
	u32 h2cq_addr;
	u32 h2cq_size;
	u32 h2cq_free;
	u32 wp, rp;

	h2cq_addr = fifo->rsvd_h2cq_addr << TX_PAGE_SIZE_SHIFT;
	h2cq_size = RSVD_PG_H2CQ_NUM << TX_PAGE_SIZE_SHIFT;

	value32 = rtw_read32(rtwdev, REG_H2C_HEAD);
	value32 = (value32 & 0xFFFC0000) | h2cq_addr;
	rtw_write32(rtwdev, REG_H2C_HEAD, value32);

	value32 = rtw_read32(rtwdev, REG_H2C_READ_ADDR);
	value32 = (value32 & 0xFFFC0000) | h2cq_addr;
	rtw_write32(rtwdev, REG_H2C_READ_ADDR, value32);

	value32 = rtw_read32(rtwdev, REG_H2C_TAIL);
	value32 &= 0xFFFC0000;
	value32 |= (h2cq_addr + h2cq_size);
	rtw_write32(rtwdev, REG_H2C_TAIL, value32);

	value8 = rtw_read8(rtwdev, REG_H2C_INFO);
	value8 = (u8)((value8 & 0xFC) | 0x01);
	rtw_write8(rtwdev, REG_H2C_INFO, value8);

	value8 = rtw_read8(rtwdev, REG_H2C_INFO);
	value8 = (u8)((value8 & 0xFB) | 0x04);
	rtw_write8(rtwdev, REG_H2C_INFO, value8);

	value8 = rtw_read8(rtwdev, REG_TXDMA_OFFSET_CHK + 1);
	value8 = (u8)((value8 & 0x7f) | 0x80);
	rtw_write8(rtwdev, REG_TXDMA_OFFSET_CHK + 1, value8);

	wp = rtw_read32(rtwdev, REG_H2C_PKT_WRITEADDR) & 0x3FFFF;
	rp = rtw_read32(rtwdev, REG_H2C_PKT_READADDR) & 0x3FFFF;
	h2cq_free = wp >= rp ? h2cq_size - (wp - rp) : rp - wp;

	if (h2cq_size != h2cq_free) {
		rtw_err(rtwdev, "H2C queue mismatch\n");
		return -EINVAL;
	}

	return 0;
}