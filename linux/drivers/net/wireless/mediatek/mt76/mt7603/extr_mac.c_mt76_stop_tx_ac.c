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
typedef  int /*<<< orphan*/  u32 ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_WF_ARB_TX_STOP_0 ; 
 int /*<<< orphan*/  mt7603_ac_queue_mask0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt76_stop_tx_ac(struct mt7603_dev *dev, u32 mask)
{
	mt76_set(dev, MT_WF_ARB_TX_STOP_0, mt7603_ac_queue_mask0(mask));
}