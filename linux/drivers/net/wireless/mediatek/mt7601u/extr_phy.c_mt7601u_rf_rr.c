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
typedef  int /*<<< orphan*/  u32 ;
struct mt7601u_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_atomic_mutex; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT7601U_STATE_REMOVED ; 
 int /*<<< orphan*/  MT7601U_STATE_WLAN_RUNNING ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG_DATA ; 
 int MT_RF_CSR_CFG_KICK ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG_REG_BANK ; 
 int /*<<< orphan*/  MT_RF_CSR_CFG_REG_ID ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rf_read (struct mt7601u_dev*,int,int,int) ; 

__attribute__((used)) static int
mt7601u_rf_rr(struct mt7601u_dev *dev, u8 bank, u8 offset)
{
	int ret = -ETIMEDOUT;
	u32 val;

	if (WARN_ON(!test_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state)) ||
	    WARN_ON(offset > 63))
		return -EINVAL;
	if (test_bit(MT7601U_STATE_REMOVED, &dev->state))
		return 0xff;

	mutex_lock(&dev->reg_atomic_mutex);

	if (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100))
		goto out;

	mt7601u_wr(dev, MT_RF_CSR_CFG,
		   FIELD_PREP(MT_RF_CSR_CFG_REG_BANK, bank) |
		   FIELD_PREP(MT_RF_CSR_CFG_REG_ID, offset) |
		   MT_RF_CSR_CFG_KICK);

	if (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100))
		goto out;

	val = mt7601u_rr(dev, MT_RF_CSR_CFG);
	if (FIELD_GET(MT_RF_CSR_CFG_REG_ID, val) == offset &&
	    FIELD_GET(MT_RF_CSR_CFG_REG_BANK, val) == bank) {
		ret = FIELD_GET(MT_RF_CSR_CFG_DATA, val);
		trace_rf_read(dev, bank, offset, ret);
	}
out:
	mutex_unlock(&dev->reg_atomic_mutex);

	if (ret < 0)
		dev_err(dev->dev, "Error: RF read %02hhx:%02hhx failed:%d!!\n",
			bank, offset, ret);

	return ret;
}