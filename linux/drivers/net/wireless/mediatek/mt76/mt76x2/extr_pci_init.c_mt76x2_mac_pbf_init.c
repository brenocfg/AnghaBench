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
 int /*<<< orphan*/  MT_PBF_RX_MAX_PCNT ; 
 int /*<<< orphan*/  MT_PBF_SYS_CTRL ; 
 int MT_PBF_SYS_CTRL_ASY_RESET ; 
 int MT_PBF_SYS_CTRL_DMA_RESET ; 
 int MT_PBF_SYS_CTRL_MAC_RESET ; 
 int MT_PBF_SYS_CTRL_MCU_RESET ; 
 int MT_PBF_SYS_CTRL_PBF_RESET ; 
 int /*<<< orphan*/  MT_PBF_TX_MAX_PCNT ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x2_mac_pbf_init(struct mt76x02_dev *dev)
{
	u32 val;

	val = MT_PBF_SYS_CTRL_MCU_RESET |
	      MT_PBF_SYS_CTRL_DMA_RESET |
	      MT_PBF_SYS_CTRL_MAC_RESET |
	      MT_PBF_SYS_CTRL_PBF_RESET |
	      MT_PBF_SYS_CTRL_ASY_RESET;

	mt76_set(dev, MT_PBF_SYS_CTRL, val);
	mt76_clear(dev, MT_PBF_SYS_CTRL, val);

	mt76_wr(dev, MT_PBF_TX_MAX_PCNT, 0xefef3f1f);
	mt76_wr(dev, MT_PBF_RX_MAX_PCNT, 0xfebf);
}