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
 int /*<<< orphan*/  write_sa2400 (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sa2400_rf_stop(struct ieee80211_hw *dev)
{
	write_sa2400(dev, 4, 0);
}