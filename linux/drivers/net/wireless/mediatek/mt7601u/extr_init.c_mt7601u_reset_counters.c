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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_RX_STA_CNT0 ; 
 int /*<<< orphan*/  MT_RX_STA_CNT1 ; 
 int /*<<< orphan*/  MT_RX_STA_CNT2 ; 
 int /*<<< orphan*/  MT_TX_STA_CNT0 ; 
 int /*<<< orphan*/  MT_TX_STA_CNT1 ; 
 int /*<<< orphan*/  MT_TX_STA_CNT2 ; 
 int /*<<< orphan*/  mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7601u_reset_counters(struct mt7601u_dev *dev)
{
	mt7601u_rr(dev, MT_RX_STA_CNT0);
	mt7601u_rr(dev, MT_RX_STA_CNT1);
	mt7601u_rr(dev, MT_RX_STA_CNT2);
	mt7601u_rr(dev, MT_TX_STA_CNT0);
	mt7601u_rr(dev, MT_TX_STA_CNT1);
	mt7601u_rr(dev, MT_TX_STA_CNT2);
}