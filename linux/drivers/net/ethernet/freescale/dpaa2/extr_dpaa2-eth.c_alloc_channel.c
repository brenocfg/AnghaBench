#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dpcon_attr {int /*<<< orphan*/  qbman_ch_id; int /*<<< orphan*/  id; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_io; TYPE_2__* net_dev; } ;
struct dpaa2_eth_channel {TYPE_3__* dpcon; struct dpaa2_eth_priv* priv; int /*<<< orphan*/  ch_id; int /*<<< orphan*/  dpcon_id; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  mc_handle; } ;
struct TYPE_7__ {struct device* parent; } ;
struct TYPE_8__ {TYPE_1__ dev; } ;

/* Variables and functions */
 struct dpaa2_eth_channel* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_3__*) ; 
 int PTR_ERR_OR_ZERO (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dpcon_get_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpcon_attr*) ; 
 int /*<<< orphan*/  free_dpcon (struct dpaa2_eth_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct dpaa2_eth_channel*) ; 
 struct dpaa2_eth_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* setup_dpcon (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static struct dpaa2_eth_channel *
alloc_channel(struct dpaa2_eth_priv *priv)
{
	struct dpaa2_eth_channel *channel;
	struct dpcon_attr attr;
	struct device *dev = priv->net_dev->dev.parent;
	int err;

	channel = kzalloc(sizeof(*channel), GFP_KERNEL);
	if (!channel)
		return NULL;

	channel->dpcon = setup_dpcon(priv);
	if (IS_ERR_OR_NULL(channel->dpcon)) {
		err = PTR_ERR_OR_ZERO(channel->dpcon);
		goto err_setup;
	}

	err = dpcon_get_attributes(priv->mc_io, 0, channel->dpcon->mc_handle,
				   &attr);
	if (err) {
		dev_err(dev, "dpcon_get_attributes() failed\n");
		goto err_get_attr;
	}

	channel->dpcon_id = attr.id;
	channel->ch_id = attr.qbman_ch_id;
	channel->priv = priv;

	return channel;

err_get_attr:
	free_dpcon(priv, channel->dpcon);
err_setup:
	kfree(channel);
	return ERR_PTR(err);
}