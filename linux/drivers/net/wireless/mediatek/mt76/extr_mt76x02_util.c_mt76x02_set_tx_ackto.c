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
typedef  scalar_t__ u8 ;
struct mt76x02_dev {int coverage_class; scalar_t__ slottime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_BKOFF_SLOT_CFG ; 
 int /*<<< orphan*/  MT_BKOFF_SLOT_CFG_SLOTTIME ; 
 int /*<<< orphan*/  MT_TX_TIMEOUT_CFG ; 
 int /*<<< orphan*/  MT_TX_TIMEOUT_CFG_ACKTO ; 
 int /*<<< orphan*/  MT_XIFS_TIME_CFG ; 
 int /*<<< orphan*/  MT_XIFS_TIME_CFG_OFDM_SIFS ; 
 scalar_t__ mt76_get_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void mt76x02_set_tx_ackto(struct mt76x02_dev *dev)
{
	u8 ackto, sifs, slottime = dev->slottime;

	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	slottime += 3 * dev->coverage_class;
	mt76_rmw_field(dev, MT_BKOFF_SLOT_CFG,
		       MT_BKOFF_SLOT_CFG_SLOTTIME, slottime);

	sifs = mt76_get_field(dev, MT_XIFS_TIME_CFG,
			      MT_XIFS_TIME_CFG_OFDM_SIFS);

	ackto = slottime + sifs;
	mt76_rmw_field(dev, MT_TX_TIMEOUT_CFG,
		       MT_TX_TIMEOUT_CFG_ACKTO, ackto);
}