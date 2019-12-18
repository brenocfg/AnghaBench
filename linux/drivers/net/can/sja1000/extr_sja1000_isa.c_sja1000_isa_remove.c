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
struct sja1000_priv {scalar_t__ read_reg; int /*<<< orphan*/  reg_base; } ;
struct platform_device {int id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SJA1000_IOSIZE ; 
 int /*<<< orphan*/  SJA1000_IOSIZE_INDIRECT ; 
 int /*<<< orphan*/  free_sja1000dev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__* mem ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * port ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sja1000_isa_port_read_reg_indirect ; 
 int /*<<< orphan*/  unregister_sja1000dev (struct net_device*) ; 

__attribute__((used)) static int sja1000_isa_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct sja1000_priv *priv = netdev_priv(dev);
	int idx = pdev->id;

	unregister_sja1000dev(dev);

	if (mem[idx]) {
		iounmap(priv->reg_base);
		release_mem_region(mem[idx], SJA1000_IOSIZE);
	} else {
		if (priv->read_reg == sja1000_isa_port_read_reg_indirect)
			release_region(port[idx], SJA1000_IOSIZE_INDIRECT);
		else
			release_region(port[idx], SJA1000_IOSIZE);
	}
	free_sja1000dev(dev);

	return 0;
}