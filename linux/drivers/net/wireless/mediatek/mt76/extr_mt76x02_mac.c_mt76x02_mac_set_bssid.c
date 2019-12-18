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
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MAC_APC_BSSID_H (int) ; 
 int /*<<< orphan*/  MT_MAC_APC_BSSID_H_ADDR ; 
 int /*<<< orphan*/  MT_MAC_APC_BSSID_L (int) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int const*) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int const*) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt76x02_mac_set_bssid(struct mt76x02_dev *dev, u8 idx, const u8 *addr)
{
	idx &= 7;
	mt76_wr(dev, MT_MAC_APC_BSSID_L(idx), get_unaligned_le32(addr));
	mt76_rmw_field(dev, MT_MAC_APC_BSSID_H(idx), MT_MAC_APC_BSSID_H_ADDR,
		       get_unaligned_le16(addr + 4));
}