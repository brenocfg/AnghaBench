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
struct hi3798cv200_priv {int /*<<< orphan*/  sample_clk; int /*<<< orphan*/  drive_clk; } ;
struct dw_mci {struct hi3798cv200_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int dw_mci_pltfm_remove (struct platform_device*) ; 
 struct dw_mci* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dw_mci_hi3798cv200_remove(struct platform_device *pdev)
{
	struct dw_mci *host = platform_get_drvdata(pdev);
	struct hi3798cv200_priv *priv = host->priv;

	clk_disable_unprepare(priv->drive_clk);
	clk_disable_unprepare(priv->sample_clk);

	return dw_mci_pltfm_remove(pdev);
}