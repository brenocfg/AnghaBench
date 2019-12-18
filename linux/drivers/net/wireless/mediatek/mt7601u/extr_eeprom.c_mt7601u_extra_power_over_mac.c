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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_PWR_CFG_1 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_2 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_4 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_7 ; 
 int /*<<< orphan*/  MT_TX_PWR_CFG_9 ; 
 int mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt7601u_extra_power_over_mac(struct mt7601u_dev *dev)
{
	u32 val;

	val = ((mt7601u_rr(dev, MT_TX_PWR_CFG_1) & 0x0000ff00) >> 8);
	val |= ((mt7601u_rr(dev, MT_TX_PWR_CFG_2) & 0x0000ff00) << 8);
	mt7601u_wr(dev, MT_TX_PWR_CFG_7, val);

	val = ((mt7601u_rr(dev, MT_TX_PWR_CFG_4) & 0x0000ff00) >> 8);
	mt7601u_wr(dev, MT_TX_PWR_CFG_9, val);
}