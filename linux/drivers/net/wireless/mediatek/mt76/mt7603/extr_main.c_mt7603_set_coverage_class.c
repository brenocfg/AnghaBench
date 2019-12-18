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
struct mt7603_dev {int /*<<< orphan*/  coverage_class; } ;
struct ieee80211_hw {struct mt7603_dev* priv; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  mt7603_mac_set_timing (struct mt7603_dev*) ; 

__attribute__((used)) static void
mt7603_set_coverage_class(struct ieee80211_hw *hw, s16 coverage_class)
{
	struct mt7603_dev *dev = hw->priv;

	dev->coverage_class = coverage_class;
	mt7603_mac_set_timing(dev);
}