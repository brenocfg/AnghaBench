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
typedef  scalar_t__ u16 ;
struct rtw_page_table {scalar_t__ exq_num; scalar_t__ nq_num; scalar_t__ lq_num; scalar_t__ hq_num; scalar_t__ gapq_num; } ;
struct rtw_fifo_conf {scalar_t__ rsvd_boundary; scalar_t__ acq_pg_num; } ;
struct TYPE_2__ {int bulkout_num; } ;
struct rtw_dev {TYPE_1__ hci; struct rtw_chip_info* chip; struct rtw_fifo_conf fifo; } ;
struct rtw_chip_info {scalar_t__ rxff_size; struct rtw_page_table* page_table; } ;

/* Variables and functions */
 int BIT_AUTO_INIT_LLT_V1 ; 
 int BIT_EN_WR_FREE_TAIL ; 
 int /*<<< orphan*/  BIT_LD_RQPN ; 
 scalar_t__ C2H_PKT_BUF ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ REG_AUTO_LLT_V1 ; 
 scalar_t__ REG_BCNQ1_BDNY_V1 ; 
 scalar_t__ REG_BCNQ_BDNY_V1 ; 
 scalar_t__ REG_CR ; 
 scalar_t__ REG_FIFOPAGE_CTRL_2 ; 
 scalar_t__ REG_FIFOPAGE_INFO_1 ; 
 scalar_t__ REG_FIFOPAGE_INFO_2 ; 
 scalar_t__ REG_FIFOPAGE_INFO_3 ; 
 scalar_t__ REG_FIFOPAGE_INFO_4 ; 
 scalar_t__ REG_FIFOPAGE_INFO_5 ; 
 scalar_t__ REG_FWHW_TXQ_CTRL ; 
 int /*<<< orphan*/  REG_RQPN_CTRL_2 ; 
 int /*<<< orphan*/  REG_RXFF_BNDY ; 
#define  RTW_HCI_TYPE_PCIE 129 
#define  RTW_HCI_TYPE_USB 128 
 int /*<<< orphan*/  check_hw_ready (struct rtw_dev*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int rtw_hci_type (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8_set (struct rtw_dev*,scalar_t__,int) ; 
 int set_trx_fifo_info (struct rtw_dev*) ; 

__attribute__((used)) static int priority_queue_cfg(struct rtw_dev *rtwdev)
{
	struct rtw_fifo_conf *fifo = &rtwdev->fifo;
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_page_table *pg_tbl = NULL;
	u16 pubq_num;
	int ret;

	ret = set_trx_fifo_info(rtwdev);
	if (ret)
		return ret;

	switch (rtw_hci_type(rtwdev)) {
	case RTW_HCI_TYPE_PCIE:
		pg_tbl = &chip->page_table[1];
		break;
	case RTW_HCI_TYPE_USB:
		if (rtwdev->hci.bulkout_num == 2)
			pg_tbl = &chip->page_table[2];
		else if (rtwdev->hci.bulkout_num == 3)
			pg_tbl = &chip->page_table[3];
		else if (rtwdev->hci.bulkout_num == 4)
			pg_tbl = &chip->page_table[4];
		else
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	pubq_num = fifo->acq_pg_num - pg_tbl->hq_num - pg_tbl->lq_num -
		   pg_tbl->nq_num - pg_tbl->exq_num - pg_tbl->gapq_num;
	rtw_write16(rtwdev, REG_FIFOPAGE_INFO_1, pg_tbl->hq_num);
	rtw_write16(rtwdev, REG_FIFOPAGE_INFO_2, pg_tbl->lq_num);
	rtw_write16(rtwdev, REG_FIFOPAGE_INFO_3, pg_tbl->nq_num);
	rtw_write16(rtwdev, REG_FIFOPAGE_INFO_4, pg_tbl->exq_num);
	rtw_write16(rtwdev, REG_FIFOPAGE_INFO_5, pubq_num);
	rtw_write32_set(rtwdev, REG_RQPN_CTRL_2, BIT_LD_RQPN);

	rtw_write16(rtwdev, REG_FIFOPAGE_CTRL_2, fifo->rsvd_boundary);
	rtw_write8_set(rtwdev, REG_FWHW_TXQ_CTRL + 2, BIT_EN_WR_FREE_TAIL >> 16);

	rtw_write16(rtwdev, REG_BCNQ_BDNY_V1, fifo->rsvd_boundary);
	rtw_write16(rtwdev, REG_FIFOPAGE_CTRL_2 + 2, fifo->rsvd_boundary);
	rtw_write16(rtwdev, REG_BCNQ1_BDNY_V1, fifo->rsvd_boundary);
	rtw_write32(rtwdev, REG_RXFF_BNDY, chip->rxff_size - C2H_PKT_BUF - 1);
	rtw_write8_set(rtwdev, REG_AUTO_LLT_V1, BIT_AUTO_INIT_LLT_V1);

	if (!check_hw_ready(rtwdev, REG_AUTO_LLT_V1, BIT_AUTO_INIT_LLT_V1, 0))
		return -EBUSY;

	rtw_write8(rtwdev, REG_CR + 3, 0);

	return 0;
}