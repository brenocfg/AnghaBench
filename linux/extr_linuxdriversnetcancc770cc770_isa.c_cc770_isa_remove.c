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
struct platform_device {int id; } ;
struct net_device {int dummy; } ;
struct cc770_priv {scalar_t__ read_reg; int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC770_IOSIZE ; 
 int /*<<< orphan*/  CC770_IOSIZE_INDIRECT ; 
 scalar_t__ cc770_isa_port_read_reg_indirect ; 
 int /*<<< orphan*/  free_cc770dev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__* mem ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * port ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_cc770dev (struct net_device*) ; 

__attribute__((used)) static int cc770_isa_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct cc770_priv *priv = netdev_priv(dev);
	int idx = pdev->id;

	unregister_cc770dev(dev);

	if (mem[idx]) {
		iounmap(priv->reg_base);
		release_mem_region(mem[idx], CC770_IOSIZE);
	} else {
		if (priv->read_reg == cc770_isa_port_read_reg_indirect)
			release_region(port[idx], CC770_IOSIZE_INDIRECT);
		else
			release_region(port[idx], CC770_IOSIZE);
	}
	free_cc770dev(dev);

	return 0;
}