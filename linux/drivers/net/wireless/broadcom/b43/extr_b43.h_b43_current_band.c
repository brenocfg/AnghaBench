#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct b43_wl {TYPE_4__* hw; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct TYPE_7__ {TYPE_2__ chandef; } ;
struct TYPE_8__ {TYPE_3__ conf; } ;
struct TYPE_5__ {int band; } ;

/* Variables and functions */

__attribute__((used)) static inline enum nl80211_band b43_current_band(struct b43_wl *wl)
{
	return wl->hw->conf.chandef.chan->band;
}