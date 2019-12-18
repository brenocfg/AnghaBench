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
struct rt2x00lib_conf {struct ieee80211_conf* conf; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_conf {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_PS ; 
 int /*<<< orphan*/  rt2800_config (struct rt2x00_dev*,struct rt2x00lib_conf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800mmio_wakeup(struct rt2x00_dev *rt2x00dev)
{
	struct ieee80211_conf conf = { .flags = 0 };
	struct rt2x00lib_conf libconf = { .conf = &conf };

	rt2800_config(rt2x00dev, &libconf, IEEE80211_CONF_CHANGE_PS);
}