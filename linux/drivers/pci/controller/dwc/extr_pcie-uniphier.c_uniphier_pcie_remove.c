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
struct uniphier_pcie_priv {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct uniphier_pcie_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uniphier_pcie_host_disable (struct uniphier_pcie_priv*) ; 

__attribute__((used)) static int uniphier_pcie_remove(struct platform_device *pdev)
{
	struct uniphier_pcie_priv *priv = platform_get_drvdata(pdev);

	uniphier_pcie_host_disable(priv);

	return 0;
}