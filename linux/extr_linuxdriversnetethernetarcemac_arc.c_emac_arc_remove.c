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
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int arc_emac_remove (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int emac_arc_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	int err;

	err = arc_emac_remove(ndev);
	free_netdev(ndev);
	return err;
}