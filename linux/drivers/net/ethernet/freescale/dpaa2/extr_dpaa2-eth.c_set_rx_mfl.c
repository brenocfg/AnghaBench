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
struct dpaa2_eth_priv {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int DPAA2_ETH_L2_MAX_FRM (int) ; 
 int DPAA2_ETH_MFL ; 
 int dpni_set_max_frame_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int set_rx_mfl(struct dpaa2_eth_priv *priv, int mtu, bool has_xdp)
{
	int mfl, err;

	/* We enforce a maximum Rx frame length based on MTU only if we have
	 * an XDP program attached (in order to avoid Rx S/G frames).
	 * Otherwise, we accept all incoming frames as long as they are not
	 * larger than maximum size supported in hardware
	 */
	if (has_xdp)
		mfl = DPAA2_ETH_L2_MAX_FRM(mtu);
	else
		mfl = DPAA2_ETH_MFL;

	err = dpni_set_max_frame_length(priv->mc_io, 0, priv->mc_token, mfl);
	if (err) {
		netdev_err(priv->net_dev, "dpni_set_max_frame_length failed\n");
		return err;
	}

	return 0;
}