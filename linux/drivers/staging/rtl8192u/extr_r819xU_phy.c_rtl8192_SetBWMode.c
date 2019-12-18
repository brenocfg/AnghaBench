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
struct r8192_priv {int SetBWModeInProgress; int CurrentChannelBW; int /*<<< orphan*/  nCur40MhzPrimeSC; } ;
struct net_device {int dummy; } ;
typedef  enum ht_extension_chan_offset { ____Placeholder_ht_extension_chan_offset } ht_extension_chan_offset ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_LOWER ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_UPPER ; 
 int HT_EXTCHNL_OFFSET_LOWER ; 
 int HT_EXTCHNL_OFFSET_UPPER ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_SetBWModeWorkItem (struct net_device*) ; 

void rtl8192_SetBWMode(struct net_device *dev,
		       enum ht_channel_width bandwidth,
		       enum ht_extension_chan_offset offset)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if (priv->SetBWModeInProgress)
		return;
	priv->SetBWModeInProgress = true;

	priv->CurrentChannelBW = bandwidth;

	if (offset == HT_EXTCHNL_OFFSET_LOWER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_UPPER;
	else if (offset == HT_EXTCHNL_OFFSET_UPPER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_LOWER;
	else
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	rtl8192_SetBWModeWorkItem(dev);

}