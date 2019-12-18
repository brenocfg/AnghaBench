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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_ARB_SCR ; 
 int MT_ARB_SCR_RX_DISABLE ; 
 int MT_ARB_SCR_TX_DISABLE ; 
 int /*<<< orphan*/  MT_WF_ARB_RQCR ; 
 int /*<<< orphan*/  MT_WF_ARB_RQCR_RX_START ; 
 int /*<<< orphan*/  MT_WF_ARB_TX_START_0 ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt7603_mac_stop(struct mt7603_dev *dev)
{
	mt76_set(dev, MT_ARB_SCR,
		 MT_ARB_SCR_TX_DISABLE | MT_ARB_SCR_RX_DISABLE);
	mt76_wr(dev, MT_WF_ARB_TX_START_0, 0);
	mt76_clear(dev, MT_WF_ARB_RQCR, MT_WF_ARB_RQCR_RX_START);
}