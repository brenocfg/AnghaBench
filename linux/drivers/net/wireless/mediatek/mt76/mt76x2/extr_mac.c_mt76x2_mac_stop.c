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
typedef  int u32 ;
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CORE ; 
 int /*<<< orphan*/  IBI ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_MAC_STATUS ; 
 int MT_MAC_STATUS_RX ; 
 int MT_MAC_STATUS_TX ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_TXOP_ED_CCA_EN ; 
 int /*<<< orphan*/  MT_TXOP_HLDR_ET ; 
 int /*<<< orphan*/  MT_TXOP_HLDR_TX40M_BLK_EN ; 
 int /*<<< orphan*/  MT_TX_RTS_CFG ; 
 int MT_TX_RTS_CFG_RETRY_LIMIT ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void mt76x2_mac_stop(struct mt76x02_dev *dev, bool force)
{
	bool stopped = false;
	u32 rts_cfg;
	int i;

	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
	mt76_clear(dev, MT_TXOP_HLDR_ET, MT_TXOP_HLDR_TX40M_BLK_EN);

	mt76_wr(dev, MT_MAC_SYS_CTRL, 0);

	rts_cfg = mt76_rr(dev, MT_TX_RTS_CFG);
	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg & ~MT_TX_RTS_CFG_RETRY_LIMIT);

	/* Wait for MAC to become idle */
	for (i = 0; i < 300; i++) {
		if ((mt76_rr(dev, MT_MAC_STATUS) &
		     (MT_MAC_STATUS_RX | MT_MAC_STATUS_TX)) ||
		    mt76_rr(dev, MT_BBP(IBI, 12))) {
			udelay(1);
			continue;
		}

		stopped = true;
		break;
	}

	if (force && !stopped) {
		mt76_set(dev, MT_BBP(CORE, 4), BIT(1));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(1));

		mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));
	}

	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg);
}