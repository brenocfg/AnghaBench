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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int flags; } ;
struct il_priv {TYPE_1__ staging; } ;

/* Variables and functions */
 int /*<<< orphan*/  RATE_1M_PLCP ; 
 int /*<<< orphan*/  RATE_6M_PLCP ; 
 int RXON_FLG_BAND_24G_MSK ; 

u8
il_get_lowest_plcp(struct il_priv *il)
{
	/*
	 * Assign the lowest rate -- should really get this from
	 * the beacon skb from mac80211.
	 */
	if (il->staging.flags & RXON_FLG_BAND_24G_MSK)
		return RATE_1M_PLCP;
	else
		return RATE_6M_PLCP;
}