#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_priv {scalar_t__ bt_traffic_load; scalar_t__ bt_full_concurrent; TYPE_2__* lib; } ;
struct TYPE_4__ {TYPE_1__* bt_params; } ;
struct TYPE_3__ {scalar_t__ advanced_bt_coexist; } ;

/* Variables and functions */
 scalar_t__ IWL_BT_COEX_TRAFFIC_LOAD_HIGH ; 
 int IWL_NUM_RX_CHAINS_MULTIPLE ; 
 int IWL_NUM_RX_CHAINS_SINGLE ; 
 scalar_t__ is_single_rx_stream (struct iwl_priv*) ; 

__attribute__((used)) static int iwl_get_active_rx_chain_count(struct iwl_priv *priv)
{
	if (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    (priv->bt_full_concurrent ||
	     priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH)) {
		/*
		 * only use chain 'A' in bt high traffic load or
		 * full concurrency mode
		 */
		return IWL_NUM_RX_CHAINS_SINGLE;
	}
	/* # of Rx chains to use when expecting MIMO. */
	if (is_single_rx_stream(priv))
		return IWL_NUM_RX_CHAINS_SINGLE;
	else
		return IWL_NUM_RX_CHAINS_MULTIPLE;
}