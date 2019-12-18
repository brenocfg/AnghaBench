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
struct sxgbe_priv_data {int tx_path_in_lpi_mode; int /*<<< orphan*/  eee_ctrl_timer; int /*<<< orphan*/  ioaddr; TYPE_2__* hw; } ;
struct TYPE_4__ {TYPE_1__* mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset_eee_mode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void sxgbe_disable_eee_mode(struct sxgbe_priv_data * const priv)
{
	/* Exit and disable EEE in case of we are are in LPI state. */
	priv->hw->mac->reset_eee_mode(priv->ioaddr);
	del_timer_sync(&priv->eee_ctrl_timer);
	priv->tx_path_in_lpi_mode = false;
}