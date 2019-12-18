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
struct mv643xx_eth_shared_private {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv643xx_eth_shared_of_remove () ; 
 struct mv643xx_eth_shared_private* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mv643xx_eth_shared_remove(struct platform_device *pdev)
{
	struct mv643xx_eth_shared_private *msp = platform_get_drvdata(pdev);

	mv643xx_eth_shared_of_remove();
	if (!IS_ERR(msp->clk))
		clk_disable_unprepare(msp->clk);
	return 0;
}