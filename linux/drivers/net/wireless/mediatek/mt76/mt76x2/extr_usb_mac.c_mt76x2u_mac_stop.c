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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  CORE ; 
 int EIO ; 
 int /*<<< orphan*/  IBI ; 
 int /*<<< orphan*/  MT76_REMOVED ; 
 int MT_BBP (int /*<<< orphan*/ ,int) ; 
 int MT_MAC_STATUS ; 
 int /*<<< orphan*/  MT_MAC_STATUS_RX ; 
 int MT_MAC_STATUS_TX ; 
 int MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int MT_TXOP_CTRL_CFG ; 
 int MT_TXOP_ED_CCA_EN ; 
 int MT_TXOP_HLDR_ET ; 
 int MT_TXOP_HLDR_TX40M_BLK_EN ; 
 int MT_TX_RTS_CFG ; 
 int MT_TX_RTS_CFG_RETRY_LIMIT ; 
 int MT_USB_DMA_CFG_RX_BUSY ; 
 int MT_USB_DMA_CFG_TX_BUSY ; 
 int /*<<< orphan*/  MT_USB_U3DMA_CFG ; 
 int MT_VEND_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt76x02_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mt76_rr (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int mt76x2u_mac_stop(struct mt76x02_dev *dev)
{
	int i, count = 0, val;
	bool stopped = false;
	u32 rts_cfg;

	if (test_bit(MT76_REMOVED, &dev->mt76.state))
		return -EIO;

	rts_cfg = mt76_rr(dev, MT_TX_RTS_CFG);
	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg & ~MT_TX_RTS_CFG_RETRY_LIMIT);

	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
	mt76_clear(dev, MT_TXOP_HLDR_ET, MT_TXOP_HLDR_TX40M_BLK_EN);

	/* wait tx dma to stop */
	for (i = 0; i < 2000; i++) {
		val = mt76_rr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG));
		if (!(val & MT_USB_DMA_CFG_TX_BUSY) && i > 10)
			break;
		usleep_range(50, 100);
	}

	/* page count on TxQ */
	for (i = 0; i < 200; i++) {
		if (!(mt76_rr(dev, 0x0438) & 0xffffffff) &&
		    !(mt76_rr(dev, 0x0a30) & 0x000000ff) &&
		    !(mt76_rr(dev, 0x0a34) & 0xff00ff00))
			break;
		usleep_range(10, 20);
	}

	/* disable tx-rx */
	mt76_clear(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_ENABLE_RX |
		   MT_MAC_SYS_CTRL_ENABLE_TX);

	/* Wait for MAC to become idle */
	for (i = 0; i < 1000; i++) {
		if (!(mt76_rr(dev, MT_MAC_STATUS) & MT_MAC_STATUS_TX) &&
		    !mt76_rr(dev, MT_BBP(IBI, 12))) {
			stopped = true;
			break;
		}
		usleep_range(10, 20);
	}

	if (!stopped) {
		mt76_set(dev, MT_BBP(CORE, 4), BIT(1));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(1));

		mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));
	}

	/* page count on RxQ */
	for (i = 0; i < 200; i++) {
		if (!(mt76_rr(dev, 0x0430) & 0x00ff0000) &&
		    !(mt76_rr(dev, 0x0a30) & 0xffffffff) &&
		    !(mt76_rr(dev, 0x0a34) & 0xffffffff) &&
		    ++count > 10)
			break;
		msleep(50);
	}

	if (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_RX, 0, 2000))
		dev_warn(dev->mt76.dev, "MAC RX failed to stop\n");

	/* wait rx dma to stop */
	for (i = 0; i < 2000; i++) {
		val = mt76_rr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG));
		if (!(val & MT_USB_DMA_CFG_RX_BUSY) && i > 10)
			break;
		usleep_range(50, 100);
	}

	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg);

	return 0;
}