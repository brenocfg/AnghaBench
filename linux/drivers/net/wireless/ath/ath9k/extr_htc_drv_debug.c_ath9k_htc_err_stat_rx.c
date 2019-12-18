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
struct ath_rx_status {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_stats; } ;
struct ath9k_htc_priv {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_cmn_debug_stat_rx (int /*<<< orphan*/ *,struct ath_rx_status*) ; 

void ath9k_htc_err_stat_rx(struct ath9k_htc_priv *priv,
			     struct ath_rx_status *rs)
{
	ath9k_cmn_debug_stat_rx(&priv->debug.rx_stats, rs);
}