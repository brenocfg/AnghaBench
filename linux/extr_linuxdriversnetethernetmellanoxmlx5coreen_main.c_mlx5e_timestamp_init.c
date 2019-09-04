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
struct TYPE_2__ {int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  tx_type; } ;
struct mlx5e_priv {TYPE_1__ tstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 

void mlx5e_timestamp_init(struct mlx5e_priv *priv)
{
	priv->tstamp.tx_type   = HWTSTAMP_TX_OFF;
	priv->tstamp.rx_filter = HWTSTAMP_FILTER_NONE;
}