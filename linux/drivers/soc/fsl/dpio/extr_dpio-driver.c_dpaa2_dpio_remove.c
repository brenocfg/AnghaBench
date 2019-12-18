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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_io; int /*<<< orphan*/  mc_handle; TYPE_1__ obj_desc; struct device dev; } ;
struct dpio_priv {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_unused_mask ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct dpio_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dpaa2_io_down (int /*<<< orphan*/ ) ; 
 int dpaa2_io_get_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpio_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpio_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpio_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpio_teardown_irqs (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpaa2_dpio_remove(struct fsl_mc_device *dpio_dev)
{
	struct device *dev;
	struct dpio_priv *priv;
	int err = 0, cpu;

	dev = &dpio_dev->dev;
	priv = dev_get_drvdata(dev);
	cpu = dpaa2_io_get_cpu(priv->io);

	dpaa2_io_down(priv->io);

	dpio_teardown_irqs(dpio_dev);

	cpumask_set_cpu(cpu, cpus_unused_mask);

	err = dpio_open(dpio_dev->mc_io, 0, dpio_dev->obj_desc.id,
			&dpio_dev->mc_handle);
	if (err) {
		dev_err(dev, "dpio_open() failed\n");
		goto err_open;
	}

	dpio_disable(dpio_dev->mc_io, 0, dpio_dev->mc_handle);

	dpio_close(dpio_dev->mc_io, 0, dpio_dev->mc_handle);

	fsl_mc_portal_free(dpio_dev->mc_io);

	return 0;

err_open:
	fsl_mc_portal_free(dpio_dev->mc_io);

	return err;
}