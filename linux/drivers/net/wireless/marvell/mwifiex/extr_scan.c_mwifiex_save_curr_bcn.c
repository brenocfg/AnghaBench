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
struct mwifiex_bssdescriptor {scalar_t__ beacon_buf_size; scalar_t__ oper_mode_offset; scalar_t__ beacon_buf; void* oper_mode; scalar_t__ ext_cap_offset; scalar_t__ bcn_ext_cap; scalar_t__ bss_co_2040_offset; scalar_t__ bcn_bss_co_2040; scalar_t__ vht_info_offset; void* bcn_vht_oper; scalar_t__ vht_cap_offset; void* bcn_vht_cap; scalar_t__ ht_info_offset; struct ieee80211_ht_operation* bcn_ht_oper; scalar_t__ ht_cap_offset; struct ieee80211_ht_cap* bcn_ht_cap; scalar_t__ rsn_offset; struct ieee_types_generic* bcn_rsn_ie; scalar_t__ wpa_offset; struct ieee_types_vendor_specific* bcn_wpa_ie; } ;
struct TYPE_2__ {struct mwifiex_bssdescriptor bss_descriptor; } ;
struct mwifiex_private {scalar_t__ curr_bcn_size; scalar_t__ curr_bcn_buf; int /*<<< orphan*/  adapter; TYPE_1__ curr_bss_params; } ;
struct ieee_types_vendor_specific {int dummy; } ;
struct ieee_types_generic {int dummy; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct ieee80211_ht_cap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
mwifiex_save_curr_bcn(struct mwifiex_private *priv)
{
	struct mwifiex_bssdescriptor *curr_bss =
		&priv->curr_bss_params.bss_descriptor;

	if (!curr_bss->beacon_buf_size)
		return;

	/* allocate beacon buffer at 1st time; or if it's size has changed */
	if (!priv->curr_bcn_buf ||
	    priv->curr_bcn_size != curr_bss->beacon_buf_size) {
		priv->curr_bcn_size = curr_bss->beacon_buf_size;

		kfree(priv->curr_bcn_buf);
		priv->curr_bcn_buf = kmalloc(curr_bss->beacon_buf_size,
					     GFP_ATOMIC);
		if (!priv->curr_bcn_buf)
			return;
	}

	memcpy(priv->curr_bcn_buf, curr_bss->beacon_buf,
	       curr_bss->beacon_buf_size);
	mwifiex_dbg(priv->adapter, INFO,
		    "info: current beacon saved %d\n",
		    priv->curr_bcn_size);

	curr_bss->beacon_buf = priv->curr_bcn_buf;

	/* adjust the pointers in the current BSS descriptor */
	if (curr_bss->bcn_wpa_ie)
		curr_bss->bcn_wpa_ie =
			(struct ieee_types_vendor_specific *)
			(curr_bss->beacon_buf +
			 curr_bss->wpa_offset);

	if (curr_bss->bcn_rsn_ie)
		curr_bss->bcn_rsn_ie = (struct ieee_types_generic *)
			(curr_bss->beacon_buf +
			 curr_bss->rsn_offset);

	if (curr_bss->bcn_ht_cap)
		curr_bss->bcn_ht_cap = (struct ieee80211_ht_cap *)
			(curr_bss->beacon_buf +
			 curr_bss->ht_cap_offset);

	if (curr_bss->bcn_ht_oper)
		curr_bss->bcn_ht_oper = (struct ieee80211_ht_operation *)
			(curr_bss->beacon_buf +
			 curr_bss->ht_info_offset);

	if (curr_bss->bcn_vht_cap)
		curr_bss->bcn_vht_cap = (void *)(curr_bss->beacon_buf +
						 curr_bss->vht_cap_offset);

	if (curr_bss->bcn_vht_oper)
		curr_bss->bcn_vht_oper = (void *)(curr_bss->beacon_buf +
						  curr_bss->vht_info_offset);

	if (curr_bss->bcn_bss_co_2040)
		curr_bss->bcn_bss_co_2040 =
			(curr_bss->beacon_buf + curr_bss->bss_co_2040_offset);

	if (curr_bss->bcn_ext_cap)
		curr_bss->bcn_ext_cap = curr_bss->beacon_buf +
			curr_bss->ext_cap_offset;

	if (curr_bss->oper_mode)
		curr_bss->oper_mode = (void *)(curr_bss->beacon_buf +
					       curr_bss->oper_mode_offset);
}