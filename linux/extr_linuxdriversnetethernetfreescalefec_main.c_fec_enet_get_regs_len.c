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
struct resource {int dummy; } ;
struct net_device {int dummy; } ;
struct fec_enet_private {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 struct resource* platform_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int resource_size (struct resource*) ; 

__attribute__((used)) static int fec_enet_get_regs_len(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct resource *r;
	int s = 0;

	r = platform_get_resource(fep->pdev, IORESOURCE_MEM, 0);
	if (r)
		s = resource_size(r);

	return s;
}