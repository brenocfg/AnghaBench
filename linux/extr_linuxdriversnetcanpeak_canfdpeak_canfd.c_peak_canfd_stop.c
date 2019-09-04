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
struct peak_canfd_priv {int /*<<< orphan*/  index; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUCAN_TX_ABORT_FLUSH ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pucan_set_reset_mode (struct peak_canfd_priv*) ; 
 int /*<<< orphan*/  pucan_tx_abort (struct peak_canfd_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void peak_canfd_stop(struct peak_canfd_priv *priv)
{
	int err;

	/* go back to RESET mode */
	err = pucan_set_reset_mode(priv);
	if (err) {
		netdev_err(priv->ndev, "channel %u reset failed\n",
			   priv->index);
	} else {
		/* abort last Tx (MUST be done in RESET mode only!) */
		pucan_tx_abort(priv, PUCAN_TX_ABORT_FLUSH);
	}
}