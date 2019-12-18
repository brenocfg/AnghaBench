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
typedef  int u16 ;
struct rtw_fifo_conf {int rsvd_boundary; } ;
struct rtw_dev {struct rtw_fifo_conf fifo; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int FIFO_DUMP_ADDR ; 
 int FIFO_PAGE_SIZE ; 
 int FIFO_PAGE_SIZE_SHIFT ; 
 int /*<<< orphan*/  REG_PKTBUF_DBG_CTRL ; 
 scalar_t__ REG_RCR ; 
 scalar_t__ RSVD_PAGE_START_ADDR ; 
 int TX_PAGE_SIZE_SHIFT ; 
 int rtw_read16 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw_read32 (struct rtw_dev*,int) ; 
 int rtw_read8 (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_warn (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int) ; 

int rtw_dump_drv_rsvd_page(struct rtw_dev *rtwdev,
			   u32 offset, u32 size, u32 *buf)
{
	struct rtw_fifo_conf *fifo = &rtwdev->fifo;
	u32 residue, i;
	u16 start_pg;
	u16 idx = 0;
	u16 ctl;
	u8 rcr;

	if (size & 0x3) {
		rtw_warn(rtwdev, "should be 4-byte aligned\n");
		return -EINVAL;
	}

	offset += fifo->rsvd_boundary << TX_PAGE_SIZE_SHIFT;
	residue = offset & (FIFO_PAGE_SIZE - 1);
	start_pg = offset >> FIFO_PAGE_SIZE_SHIFT;
	start_pg += RSVD_PAGE_START_ADDR;

	rcr = rtw_read8(rtwdev, REG_RCR + 2);
	ctl = rtw_read16(rtwdev, REG_PKTBUF_DBG_CTRL) & 0xf000;

	/* disable rx clock gate */
	rtw_write8(rtwdev, REG_RCR, rcr | BIT(3));

	do {
		rtw_write16(rtwdev, REG_PKTBUF_DBG_CTRL, start_pg | ctl);

		for (i = FIFO_DUMP_ADDR + residue;
		     i < FIFO_DUMP_ADDR + FIFO_PAGE_SIZE; i += 4) {
			buf[idx++] = rtw_read32(rtwdev, i);
			size -= 4;
			if (size == 0)
				goto out;
		}

		residue = 0;
		start_pg++;
	} while (size);

out:
	rtw_write16(rtwdev, REG_PKTBUF_DBG_CTRL, ctl);
	rtw_write8(rtwdev, REG_RCR + 2, rcr);
	return 0;
}