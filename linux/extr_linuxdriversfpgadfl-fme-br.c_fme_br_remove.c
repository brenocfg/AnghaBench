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
struct platform_device {int dummy; } ;
struct fpga_bridge {struct fme_br_priv* priv; } ;
struct fme_br_priv {scalar_t__ port_ops; TYPE_1__* port_pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dfl_fpga_port_ops_put (scalar_t__) ; 
 int /*<<< orphan*/  fpga_bridge_unregister (struct fpga_bridge*) ; 
 struct fpga_bridge* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fme_br_remove(struct platform_device *pdev)
{
	struct fpga_bridge *br = platform_get_drvdata(pdev);
	struct fme_br_priv *priv = br->priv;

	fpga_bridge_unregister(br);

	if (priv->port_pdev)
		put_device(&priv->port_pdev->dev);
	if (priv->port_ops)
		dfl_fpga_port_ops_put(priv->port_ops);

	return 0;
}