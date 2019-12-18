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
struct iwl_vif_priv {struct iwl_rxon_context* ctx; } ;
struct iwl_rxon_context {int dummy; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct iwl_rxon_context *
iwl_rxon_ctx_from_vif(struct ieee80211_vif *vif)
{
	struct iwl_vif_priv *vif_priv = (void *)vif->drv_priv;

	return vif_priv->ctx;
}