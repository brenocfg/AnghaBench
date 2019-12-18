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
struct wcn36xx_sta {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct wcn36xx_sta *wcn36xx_sta_to_priv(struct ieee80211_sta *sta)
{
	return (struct wcn36xx_sta *)sta->drv_priv;
}