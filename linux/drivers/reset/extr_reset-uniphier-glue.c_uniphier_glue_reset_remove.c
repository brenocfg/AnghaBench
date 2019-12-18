#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uniphier_glue_reset_priv {int /*<<< orphan*/  clk; TYPE_1__* data; int /*<<< orphan*/ * rst; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int nrsts; int /*<<< orphan*/  nclks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uniphier_glue_reset_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_glue_reset_remove(struct platform_device *pdev)
{
	struct uniphier_glue_reset_priv *priv = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < priv->data->nrsts; i++)
		reset_control_assert(priv->rst[i]);

	clk_bulk_disable_unprepare(priv->data->nclks, priv->clk);

	return 0;
}