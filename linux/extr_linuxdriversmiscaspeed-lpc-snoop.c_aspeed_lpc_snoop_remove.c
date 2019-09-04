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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct aspeed_lpc_snoop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_lpc_disable_snoop (struct aspeed_lpc_snoop*,int) ; 
 struct aspeed_lpc_snoop* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aspeed_lpc_snoop_remove(struct platform_device *pdev)
{
	struct aspeed_lpc_snoop *lpc_snoop = dev_get_drvdata(&pdev->dev);

	/* Disable both snoop channels */
	aspeed_lpc_disable_snoop(lpc_snoop, 0);
	aspeed_lpc_disable_snoop(lpc_snoop, 1);

	return 0;
}