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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_handle; int /*<<< orphan*/  mc_io; TYPE_1__ obj_desc; struct device dev; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; int /*<<< orphan*/  cls_rules; int /*<<< orphan*/  dpni_attrs; int /*<<< orphan*/  dpni_ver_minor; int /*<<< orphan*/  dpni_ver_major; } ;
struct dpaa2_eth_cls_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_VER_MAJOR ; 
 int /*<<< orphan*/  DPNI_VER_MINOR ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dpaa2_eth_cmp_dpni_ver (struct dpaa2_eth_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpaa2_eth_fs_count (struct dpaa2_eth_priv*) ; 
 scalar_t__ dpaa2_eth_has_pause_support (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dpni_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpni_get_api_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dpni_get_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dpni_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dpni_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int set_buffer_layout (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  set_enqueue_mode (struct dpaa2_eth_priv*) ; 
 int set_pause (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static int setup_dpni(struct fsl_mc_device *ls_dev)
{
	struct device *dev = &ls_dev->dev;
	struct dpaa2_eth_priv *priv;
	struct net_device *net_dev;
	int err;

	net_dev = dev_get_drvdata(dev);
	priv = netdev_priv(net_dev);

	/* get a handle for the DPNI object */
	err = dpni_open(priv->mc_io, 0, ls_dev->obj_desc.id, &priv->mc_token);
	if (err) {
		dev_err(dev, "dpni_open() failed\n");
		return err;
	}

	/* Check if we can work with this DPNI object */
	err = dpni_get_api_version(priv->mc_io, 0, &priv->dpni_ver_major,
				   &priv->dpni_ver_minor);
	if (err) {
		dev_err(dev, "dpni_get_api_version() failed\n");
		goto close;
	}
	if (dpaa2_eth_cmp_dpni_ver(priv, DPNI_VER_MAJOR, DPNI_VER_MINOR) < 0) {
		dev_err(dev, "DPNI version %u.%u not supported, need >= %u.%u\n",
			priv->dpni_ver_major, priv->dpni_ver_minor,
			DPNI_VER_MAJOR, DPNI_VER_MINOR);
		err = -ENOTSUPP;
		goto close;
	}

	ls_dev->mc_io = priv->mc_io;
	ls_dev->mc_handle = priv->mc_token;

	err = dpni_reset(priv->mc_io, 0, priv->mc_token);
	if (err) {
		dev_err(dev, "dpni_reset() failed\n");
		goto close;
	}

	err = dpni_get_attributes(priv->mc_io, 0, priv->mc_token,
				  &priv->dpni_attrs);
	if (err) {
		dev_err(dev, "dpni_get_attributes() failed (err=%d)\n", err);
		goto close;
	}

	err = set_buffer_layout(priv);
	if (err)
		goto close;

	set_enqueue_mode(priv);

	/* Enable pause frame support */
	if (dpaa2_eth_has_pause_support(priv)) {
		err = set_pause(priv);
		if (err)
			goto close;
	}

	priv->cls_rules = devm_kzalloc(dev, sizeof(struct dpaa2_eth_cls_rule) *
				       dpaa2_eth_fs_count(priv), GFP_KERNEL);
	if (!priv->cls_rules)
		goto close;

	return 0;

close:
	dpni_close(priv->mc_io, 0, priv->mc_token);

	return err;
}