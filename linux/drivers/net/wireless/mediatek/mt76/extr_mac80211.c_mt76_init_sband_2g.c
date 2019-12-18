#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sband; } ;
struct mt76_dev {TYPE_3__ sband_2g; TYPE_2__* hw; } ;
struct ieee80211_rate {int dummy; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  mt76_channels_2ghz ; 
 int mt76_init_sband (struct mt76_dev*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_rate*,int,int) ; 

__attribute__((used)) static int
mt76_init_sband_2g(struct mt76_dev *dev, struct ieee80211_rate *rates,
		   int n_rates)
{
	dev->hw->wiphy->bands[NL80211_BAND_2GHZ] = &dev->sband_2g.sband;

	return mt76_init_sband(dev, &dev->sband_2g,
			       mt76_channels_2ghz,
			       ARRAY_SIZE(mt76_channels_2ghz),
			       rates, n_rates, false);
}