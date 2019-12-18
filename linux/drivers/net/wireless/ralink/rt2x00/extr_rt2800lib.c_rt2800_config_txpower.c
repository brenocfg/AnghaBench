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
struct rt2x00_dev {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT3593 ; 
 int /*<<< orphan*/  RT3883 ; 
 int /*<<< orphan*/  RT6352 ; 
 int /*<<< orphan*/  rt2800_config_txpower_rt28xx (struct rt2x00_dev*,struct ieee80211_channel*,int) ; 
 int /*<<< orphan*/  rt2800_config_txpower_rt3593 (struct rt2x00_dev*,struct ieee80211_channel*,int) ; 
 int /*<<< orphan*/  rt2800_config_txpower_rt6352 (struct rt2x00_dev*,struct ieee80211_channel*,int) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_config_txpower(struct rt2x00_dev *rt2x00dev,
				  struct ieee80211_channel *chan,
				  int power_level)
{
	if (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		rt2800_config_txpower_rt3593(rt2x00dev, chan, power_level);
	else if (rt2x00_rt(rt2x00dev, RT6352))
		rt2800_config_txpower_rt6352(rt2x00dev, chan, power_level);
	else
		rt2800_config_txpower_rt28xx(rt2x00dev, chan, power_level);
}