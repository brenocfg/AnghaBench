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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;
struct mt76x02_dev {TYPE_1__ mt76; int /*<<< orphan*/  phy_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT76_REMOVED ; 
 int MT_RF_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG_DATA ; 
 int MT_RF_CSR_CFG_KICK ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG_REG_BANK ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG_REG_ID ; 
 int MT_RF_CSR_CFG_WR ; 
 int MT_RF_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76x0_rf_csr_wr(struct mt76x02_dev *dev, u32 offset, u8 value)
{
	int ret = 0;
	u8 bank, reg;

	if (test_bit(MT76_REMOVED, &dev->mt76.state))
		return -ENODEV;

	bank = MT_RF_BANK(offset);
	reg = MT_RF_REG(offset);

	if (WARN_ON_ONCE(reg > 127) || WARN_ON_ONCE(bank > 8))
		return -EINVAL;

	mutex_lock(&dev->phy_mutex);

	if (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100)) {
		ret = -ETIMEDOUT;
		goto out;
	}

	mt76_wr(dev, MT_RF_CSR_CFG,
		FIELD_PREP(MT_RF_CSR_CFG_DATA, value) |
		FIELD_PREP(MT_RF_CSR_CFG_REG_BANK, bank) |
		FIELD_PREP(MT_RF_CSR_CFG_REG_ID, reg) |
		MT_RF_CSR_CFG_WR |
		MT_RF_CSR_CFG_KICK);

out:
	mutex_unlock(&dev->phy_mutex);

	if (ret < 0)
		dev_err(dev->mt76.dev, "Error: RF write %d:%d failed:%d!!\n",
			bank, reg, ret);

	return ret;
}