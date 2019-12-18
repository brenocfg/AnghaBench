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
struct mt76x02_dev {int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_CH_TIME_CFG ; 
 int MT_CH_TIME_CFG_EIFS_AS_BUSY ; 
 int MT_CH_TIME_CFG_NAV_AS_BUSY ; 
 int MT_CH_TIME_CFG_RX_AS_BUSY ; 
 int MT_CH_TIME_CFG_TIMER_EN ; 
 int MT_CH_TIME_CFG_TX_AS_BUSY ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_TXOP_EXT_CCA_DLY ; 
 int /*<<< orphan*/  MT_TXOP_TRUN_EN ; 
 int /*<<< orphan*/  MT_US_CYC_CFG ; 
 int /*<<< orphan*/  MT_US_CYC_CNT ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_wait_for_mac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02u_init_beacon_config (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_chip_onoff (struct mt76x02_dev*,int,int) ; 
 int mt76x0_init_hardware (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_init_usb_dma (struct mt76x02_dev*) ; 
 int mt76x0u_mcu_init (struct mt76x02_dev*) ; 

__attribute__((used)) static int mt76x0u_init_hardware(struct mt76x02_dev *dev, bool reset)
{
	int err;

	mt76x0_chip_onoff(dev, true, reset);

	if (!mt76x02_wait_for_mac(&dev->mt76))
		return -ETIMEDOUT;

	err = mt76x0u_mcu_init(dev);
	if (err < 0)
		return err;

	mt76x0_init_usb_dma(dev);
	err = mt76x0_init_hardware(dev);
	if (err < 0)
		return err;

	mt76x02u_init_beacon_config(dev);

	mt76_rmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);
	mt76_wr(dev, MT_TXOP_CTRL_CFG,
		FIELD_PREP(MT_TXOP_TRUN_EN, 0x3f) |
		FIELD_PREP(MT_TXOP_EXT_CCA_DLY, 0x58));

	mt76_wr(dev, MT_CH_TIME_CFG,
		MT_CH_TIME_CFG_TIMER_EN |
		MT_CH_TIME_CFG_TX_AS_BUSY |
		MT_CH_TIME_CFG_RX_AS_BUSY |
		MT_CH_TIME_CFG_NAV_AS_BUSY |
		MT_CH_TIME_CFG_EIFS_AS_BUSY);

	return 0;
}