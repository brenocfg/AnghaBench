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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt7603_dev {TYPE_1__ mt76; int /*<<< orphan*/  rxfilter; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int MT7603_WTBL_SIZE ; 
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MT_INT_SOURCE_CSR ; 
 int /*<<< orphan*/  MT_PSE_RTA ; 
 int MT_PSE_RTA_BUSY ; 
 int /*<<< orphan*/  MT_PSE_RTA_TAG_ID ; 
 int MT_PSE_RTA_WRITE ; 
 int /*<<< orphan*/  MT_WF_RFCR ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int mt7603_dma_init (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_dma_sched_init (struct mt7603_dev*) ; 
 int mt7603_eeprom_init (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_mac_dma_start (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_mac_init (struct mt7603_dev*) ; 
 int mt7603_mcu_init (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_mcu_set_eeprom (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_phy_init (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7603_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt7603_init_hardware(struct mt7603_dev *dev)
{
	int i, ret;

	mt76_wr(dev, MT_INT_SOURCE_CSR, ~0);

	ret = mt7603_eeprom_init(dev);
	if (ret < 0)
		return ret;

	ret = mt7603_dma_init(dev);
	if (ret)
		return ret;

	mt76_wr(dev, MT_WPDMA_GLO_CFG, 0x52000850);
	mt7603_mac_dma_start(dev);
	dev->rxfilter = mt76_rr(dev, MT_WF_RFCR);
	set_bit(MT76_STATE_INITIALIZED, &dev->mt76.state);

	for (i = 0; i < MT7603_WTBL_SIZE; i++) {
		mt76_wr(dev, MT_PSE_RTA, MT_PSE_RTA_BUSY | MT_PSE_RTA_WRITE |
			FIELD_PREP(MT_PSE_RTA_TAG_ID, i));
		mt76_poll(dev, MT_PSE_RTA, MT_PSE_RTA_BUSY, 0, 5000);
	}

	ret = mt7603_mcu_init(dev);
	if (ret)
		return ret;

	mt7603_dma_sched_init(dev);
	mt7603_mcu_set_eeprom(dev);
	mt7603_phy_init(dev);
	mt7603_mac_init(dev);

	return 0;
}