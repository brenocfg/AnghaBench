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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * OFDM_CONFIG ; 
 int /*<<< orphan*/  rtl8225se_write_phy_ofdm (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8187se_write_ofdm_config(struct ieee80211_hw *dev)
{
	/* write OFDM_CONFIG table */
	int i;

	for (i = 0; i < 60; i++)
		rtl8225se_write_phy_ofdm(dev, i, OFDM_CONFIG[i]);

}