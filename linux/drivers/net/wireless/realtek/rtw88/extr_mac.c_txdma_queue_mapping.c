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
typedef  int /*<<< orphan*/  u16 ;
struct rtw_rqpn {int /*<<< orphan*/  dma_map_vo; int /*<<< orphan*/  dma_map_vi; int /*<<< orphan*/  dma_map_be; int /*<<< orphan*/  dma_map_bk; int /*<<< orphan*/  dma_map_mg; int /*<<< orphan*/  dma_map_hi; } ;
struct TYPE_2__ {int bulkout_num; } ;
struct rtw_dev {TYPE_1__ hci; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {struct rtw_rqpn* rqpn_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_H2CQ_FULL ; 
 int /*<<< orphan*/  BIT_TXDMA_BEQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_BKQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_HIQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_MGQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_VIQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_VOQ_MAP (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAC_TRX_ENABLE ; 
 int /*<<< orphan*/  REG_CR ; 
 int /*<<< orphan*/  REG_H2CQ_CSR ; 
 int /*<<< orphan*/  REG_TXDMA_PQ_MAP ; 
#define  RTW_HCI_TYPE_PCIE 129 
#define  RTW_HCI_TYPE_USB 128 
 int rtw_hci_type (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int txdma_queue_mapping(struct rtw_dev *rtwdev)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_rqpn *rqpn = NULL;
	u16 txdma_pq_map = 0;

	switch (rtw_hci_type(rtwdev)) {
	case RTW_HCI_TYPE_PCIE:
		rqpn = &chip->rqpn_table[1];
		break;
	case RTW_HCI_TYPE_USB:
		if (rtwdev->hci.bulkout_num == 2)
			rqpn = &chip->rqpn_table[2];
		else if (rtwdev->hci.bulkout_num == 3)
			rqpn = &chip->rqpn_table[3];
		else if (rtwdev->hci.bulkout_num == 4)
			rqpn = &chip->rqpn_table[4];
		else
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	txdma_pq_map |= BIT_TXDMA_HIQ_MAP(rqpn->dma_map_hi);
	txdma_pq_map |= BIT_TXDMA_MGQ_MAP(rqpn->dma_map_mg);
	txdma_pq_map |= BIT_TXDMA_BKQ_MAP(rqpn->dma_map_bk);
	txdma_pq_map |= BIT_TXDMA_BEQ_MAP(rqpn->dma_map_be);
	txdma_pq_map |= BIT_TXDMA_VIQ_MAP(rqpn->dma_map_vi);
	txdma_pq_map |= BIT_TXDMA_VOQ_MAP(rqpn->dma_map_vo);
	rtw_write16(rtwdev, REG_TXDMA_PQ_MAP, txdma_pq_map);

	rtw_write8(rtwdev, REG_CR, 0);
	rtw_write8(rtwdev, REG_CR, MAC_TRX_ENABLE);
	rtw_write32(rtwdev, REG_H2CQ_CSR, BIT_H2CQ_FULL);

	return 0;
}