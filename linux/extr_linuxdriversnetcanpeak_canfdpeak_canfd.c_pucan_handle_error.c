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
struct pucan_error_msg {int /*<<< orphan*/  rx_err_cnt; int /*<<< orphan*/  tx_err_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; } ;
struct peak_canfd_priv {TYPE_1__ bec; } ;

/* Variables and functions */

__attribute__((used)) static int pucan_handle_error(struct peak_canfd_priv *priv,
			      struct pucan_error_msg *msg)
{
	priv->bec.txerr = msg->tx_err_cnt;
	priv->bec.rxerr = msg->rx_err_cnt;

	return 0;
}