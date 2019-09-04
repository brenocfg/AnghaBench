#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rings; } ;
struct safexcel_crypto_priv {TYPE_2__* ring; TYPE_1__ config; int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct safexcel_crypto_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  safexcel_hw_reset_rings (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  safexcel_unregister_algorithms (struct safexcel_crypto_priv*) ; 

__attribute__((used)) static int safexcel_remove(struct platform_device *pdev)
{
	struct safexcel_crypto_priv *priv = platform_get_drvdata(pdev);
	int i;

	safexcel_unregister_algorithms(priv);
	safexcel_hw_reset_rings(priv);

	clk_disable_unprepare(priv->clk);

	for (i = 0; i < priv->config.rings; i++)
		destroy_workqueue(priv->ring[i].workqueue);

	return 0;
}