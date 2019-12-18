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
 int /*<<< orphan*/  eth_port_reset (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void pxa168_eth_shutdown(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	eth_port_reset(dev);
}