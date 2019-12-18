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
struct xdp_rxq_info {int dummy; } ;
struct cpsw_priv {struct xdp_rxq_info* xdp_rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdp_rxq_info_is_reg (struct xdp_rxq_info*) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (struct xdp_rxq_info*) ; 

__attribute__((used)) static void cpsw_ndev_destroy_xdp_rxq(struct cpsw_priv *priv, int ch)
{
	struct xdp_rxq_info *rxq = &priv->xdp_rxq[ch];

	if (!xdp_rxq_info_is_reg(rxq))
		return;

	xdp_rxq_info_unreg(rxq);
}