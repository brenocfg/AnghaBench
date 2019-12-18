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
struct TYPE_4__ {int ctrlmode; } ;
struct TYPE_3__ {scalar_t__ rxerr; scalar_t__ txerr; } ;
struct peak_canfd_priv {TYPE_2__ can; TYPE_1__ bec; scalar_t__ echo_idx; } ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int pucan_clr_err_counters (struct peak_canfd_priv*) ; 
 int pucan_set_listen_only_mode (struct peak_canfd_priv*) ; 
 int pucan_set_normal_mode (struct peak_canfd_priv*) ; 

__attribute__((used)) static int peak_canfd_start(struct peak_canfd_priv *priv)
{
	int err;

	err = pucan_clr_err_counters(priv);
	if (err)
		goto err_exit;

	priv->echo_idx = 0;

	priv->bec.txerr = 0;
	priv->bec.rxerr = 0;

	if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		err = pucan_set_listen_only_mode(priv);
	else
		err = pucan_set_normal_mode(priv);

err_exit:
	return err;
}