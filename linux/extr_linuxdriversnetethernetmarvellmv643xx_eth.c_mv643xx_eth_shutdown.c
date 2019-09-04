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
struct mv643xx_eth_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  port_reset (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv643xx_eth_shutdown(struct platform_device *pdev)
{
	struct mv643xx_eth_private *mp = platform_get_drvdata(pdev);

	/* Mask all interrupts on ethernet port */
	wrlp(mp, INT_MASK, 0);
	rdlp(mp, INT_MASK);

	if (netif_running(mp->dev))
		port_reset(mp);
}