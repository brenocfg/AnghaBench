#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dpni_link_cfg {int /*<<< orphan*/  options; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  options; } ;
struct dpaa2_eth_priv {TYPE_1__ link_state; int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; TYPE_3__* net_dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_LINK_OPT_ASYM_PAUSE ; 
 int /*<<< orphan*/  DPNI_LINK_OPT_PAUSE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dpni_get_link_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_link_cfg*) ; 
 int dpni_set_link_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_link_cfg*) ; 

__attribute__((used)) static int set_pause(struct dpaa2_eth_priv *priv)
{
	struct device *dev = priv->net_dev->dev.parent;
	struct dpni_link_cfg link_cfg = {0};
	int err;

	/* Get the default link options so we don't override other flags */
	err = dpni_get_link_cfg(priv->mc_io, 0, priv->mc_token, &link_cfg);
	if (err) {
		dev_err(dev, "dpni_get_link_cfg() failed\n");
		return err;
	}

	/* By default, enable both Rx and Tx pause frames */
	link_cfg.options |= DPNI_LINK_OPT_PAUSE;
	link_cfg.options &= ~DPNI_LINK_OPT_ASYM_PAUSE;
	err = dpni_set_link_cfg(priv->mc_io, 0, priv->mc_token, &link_cfg);
	if (err) {
		dev_err(dev, "dpni_set_link_cfg() failed\n");
		return err;
	}

	priv->link_state.options = link_cfg.options;

	return 0;
}