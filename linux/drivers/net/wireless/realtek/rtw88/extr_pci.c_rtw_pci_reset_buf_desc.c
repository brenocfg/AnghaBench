#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rtw_pci {TYPE_2__* rx_rings; TYPE_4__* tx_rings; } ;
struct rtw_dev {scalar_t__ priv; } ;
typedef  int dma_addr_t ;
struct TYPE_7__ {int dma; int len; scalar_t__ wp; scalar_t__ rp; } ;
struct TYPE_8__ {TYPE_3__ r; } ;
struct TYPE_5__ {int len; int dma; scalar_t__ wp; scalar_t__ rp; } ;
struct TYPE_6__ {TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CLR_H2CQ_HOST_IDX ; 
 int /*<<< orphan*/  BIT_CLR_H2CQ_HW_IDX ; 
 scalar_t__ RTK_PCI_CTRL ; 
 int /*<<< orphan*/  RTK_PCI_RXBD_DESA_MPDUQ ; 
 int /*<<< orphan*/  RTK_PCI_RXBD_NUM_MPDUQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_BCNQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_BEQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_BKQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_H2CQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_HI0Q ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_MGMTQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_VIQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_DESA_VOQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_H2CQ_CSR ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_NUM_BEQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_NUM_BKQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_NUM_H2CQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_NUM_HI0Q ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_NUM_MGMTQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_NUM_VIQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_NUM_VOQ ; 
 int /*<<< orphan*/  RTK_PCI_TXBD_RWPTR_CLR ; 
 size_t RTW_RX_QUEUE_MPDU ; 
 size_t RTW_TX_QUEUE_BCN ; 
 size_t RTW_TX_QUEUE_BE ; 
 size_t RTW_TX_QUEUE_BK ; 
 size_t RTW_TX_QUEUE_H2C ; 
 size_t RTW_TX_QUEUE_HI0 ; 
 size_t RTW_TX_QUEUE_MGMT ; 
 size_t RTW_TX_QUEUE_VI ; 
 size_t RTW_TX_QUEUE_VO ; 
 int rtw_read8 (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int) ; 

__attribute__((used)) static void rtw_pci_reset_buf_desc(struct rtw_dev *rtwdev)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;
	u32 len;
	u8 tmp;
	dma_addr_t dma;

	tmp = rtw_read8(rtwdev, RTK_PCI_CTRL + 3);
	rtw_write8(rtwdev, RTK_PCI_CTRL + 3, tmp | 0xf7);

	dma = rtwpci->tx_rings[RTW_TX_QUEUE_BCN].r.dma;
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_BCNQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_TXBD_NUM_H2CQ, len);
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_H2CQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_TXBD_NUM_BKQ, len);
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_BKQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_TXBD_NUM_BEQ, len);
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_BEQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_TXBD_NUM_VOQ, len);
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_VOQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_TXBD_NUM_VIQ, len);
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_VIQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_TXBD_NUM_MGMTQ, len);
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_MGMTQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_TXBD_NUM_HI0Q, len);
	rtw_write32(rtwdev, RTK_PCI_TXBD_DESA_HI0Q, dma);

	len = rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.len;
	dma = rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.dma;
	rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.rp = 0;
	rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.wp = 0;
	rtw_write16(rtwdev, RTK_PCI_RXBD_NUM_MPDUQ, len & 0xfff);
	rtw_write32(rtwdev, RTK_PCI_RXBD_DESA_MPDUQ, dma);

	/* reset read/write point */
	rtw_write32(rtwdev, RTK_PCI_TXBD_RWPTR_CLR, 0xffffffff);

	/* rest H2C Queue index */
	rtw_write32_set(rtwdev, RTK_PCI_TXBD_H2CQ_CSR, BIT_CLR_H2CQ_HOST_IDX);
	rtw_write32_set(rtwdev, RTK_PCI_TXBD_H2CQ_CSR, BIT_CLR_H2CQ_HW_IDX);
}