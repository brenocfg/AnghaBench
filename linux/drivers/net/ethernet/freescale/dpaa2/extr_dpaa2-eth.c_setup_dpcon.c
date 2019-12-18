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
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_handle; TYPE_3__ obj_desc; } ;
struct dpcon_attr {int dummy; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_io; TYPE_2__* net_dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int EPROBE_DEFER ; 
 struct fsl_mc_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  FSL_MC_POOL_DPCON ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dpcon_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpcon_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpcon_get_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpcon_attr*) ; 
 int dpcon_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dpcon_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsl_mc_object_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fsl_mc_device**) ; 
 int /*<<< orphan*/  fsl_mc_object_free (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  to_fsl_mc_device (struct device*) ; 

__attribute__((used)) static struct fsl_mc_device *setup_dpcon(struct dpaa2_eth_priv *priv)
{
	struct fsl_mc_device *dpcon;
	struct device *dev = priv->net_dev->dev.parent;
	struct dpcon_attr attrs;
	int err;

	err = fsl_mc_object_allocate(to_fsl_mc_device(dev),
				     FSL_MC_POOL_DPCON, &dpcon);
	if (err) {
		if (err == -ENXIO)
			err = -EPROBE_DEFER;
		else
			dev_info(dev, "Not enough DPCONs, will go on as-is\n");
		return ERR_PTR(err);
	}

	err = dpcon_open(priv->mc_io, 0, dpcon->obj_desc.id, &dpcon->mc_handle);
	if (err) {
		dev_err(dev, "dpcon_open() failed\n");
		goto free;
	}

	err = dpcon_reset(priv->mc_io, 0, dpcon->mc_handle);
	if (err) {
		dev_err(dev, "dpcon_reset() failed\n");
		goto close;
	}

	err = dpcon_get_attributes(priv->mc_io, 0, dpcon->mc_handle, &attrs);
	if (err) {
		dev_err(dev, "dpcon_get_attributes() failed\n");
		goto close;
	}

	err = dpcon_enable(priv->mc_io, 0, dpcon->mc_handle);
	if (err) {
		dev_err(dev, "dpcon_enable() failed\n");
		goto close;
	}

	return dpcon;

close:
	dpcon_close(priv->mc_io, 0, dpcon->mc_handle);
free:
	fsl_mc_object_free(dpcon);

	return NULL;
}