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
typedef  size_t u8 ;
struct iwl_priv {scalar_t__ num_stations; int /*<<< orphan*/  sta_lock; TYPE_1__* stations; int /*<<< orphan*/ ** tid_data; } ;
struct TYPE_2__ {int used; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_ASSOC (struct iwl_priv*,char*,size_t const*,size_t const) ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,size_t const*) ; 
 size_t const IWL_INVALID_STATION ; 
 size_t IWL_MAX_TID_COUNT ; 
 int IWL_STA_DRIVER_ACTIVE ; 
 int IWL_STA_UCODE_INPROGRESS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_is_ready (struct iwl_priv*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_deactivate_station(struct iwl_priv *priv, const u8 sta_id,
			    const u8 *addr)
{
	u8 tid;

	if (!iwl_is_ready(priv)) {
		IWL_DEBUG_INFO(priv,
			"Unable to remove station %pM, device not ready.\n",
			addr);
		return;
	}

	IWL_DEBUG_ASSOC(priv, "Deactivating STA: %pM (%d)\n", addr, sta_id);

	if (WARN_ON_ONCE(sta_id == IWL_INVALID_STATION))
		return;

	spin_lock_bh(&priv->sta_lock);

	WARN_ON_ONCE(!(priv->stations[sta_id].used & IWL_STA_DRIVER_ACTIVE));

	for (tid = 0; tid < IWL_MAX_TID_COUNT; tid++)
		memset(&priv->tid_data[sta_id][tid], 0,
			sizeof(priv->tid_data[sta_id][tid]));

	priv->stations[sta_id].used &= ~IWL_STA_DRIVER_ACTIVE;
	priv->stations[sta_id].used &= ~IWL_STA_UCODE_INPROGRESS;

	priv->num_stations--;

	if (WARN_ON_ONCE(priv->num_stations < 0))
		priv->num_stations = 0;

	spin_unlock_bh(&priv->sta_lock);
}