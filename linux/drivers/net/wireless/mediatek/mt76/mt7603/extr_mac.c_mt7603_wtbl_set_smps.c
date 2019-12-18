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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;
struct mt7603_sta {int smps; TYPE_1__ wcid; } ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_WTBL1_W2_SMPS ; 
 scalar_t__ mt7603_wtbl1_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7603_dev*,scalar_t__,int /*<<< orphan*/ ,int) ; 

void mt7603_wtbl_set_smps(struct mt7603_dev *dev, struct mt7603_sta *sta,
			  bool enabled)
{
	u32 addr = mt7603_wtbl1_addr(sta->wcid.idx);

	if (sta->smps == enabled)
		return;

	mt76_rmw_field(dev, addr + 2 * 4, MT_WTBL1_W2_SMPS, enabled);
	sta->smps = enabled;
}