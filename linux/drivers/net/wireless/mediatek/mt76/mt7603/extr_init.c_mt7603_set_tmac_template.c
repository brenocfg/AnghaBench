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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_CLIENT_BASE_PHYS_ADDR ; 
 int MT_CLIENT_TMAC_INFO_TEMPLATE ; 
 int /*<<< orphan*/  MT_TXD3_REM_TX_COUNT ; 
 int MT_TXD5_SW_POWER_MGMT ; 
 int mt7603_reg_map (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int,int) ; 

__attribute__((used)) static void
mt7603_set_tmac_template(struct mt7603_dev *dev)
{
	u32 desc[5] = {
		[1] = FIELD_PREP(MT_TXD3_REM_TX_COUNT, 0xf),
		[3] = MT_TXD5_SW_POWER_MGMT
	};
	u32 addr;
	int i;

	addr = mt7603_reg_map(dev, MT_CLIENT_BASE_PHYS_ADDR);
	addr += MT_CLIENT_TMAC_INFO_TEMPLATE;
	for (i = 0; i < ARRAY_SIZE(desc); i++)
		mt76_wr(dev, addr + 4 * i, desc[i]);
}