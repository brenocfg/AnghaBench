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
struct tegra_sor {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_dp; int /*<<< orphan*/  clk_safe; int /*<<< orphan*/  dev; scalar_t__ aux; int /*<<< orphan*/  output; } ;
struct host1x_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOR_INT_ENABLE ; 
 int /*<<< orphan*/  SOR_INT_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_dp_aux_detach (scalar_t__) ; 
 struct tegra_sor* host1x_client_to_sor (struct host1x_client*) ; 
 int /*<<< orphan*/  tegra_output_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_sor_exit(struct host1x_client *client)
{
	struct tegra_sor *sor = host1x_client_to_sor(client);
	int err;

	tegra_sor_writel(sor, 0, SOR_INT_MASK);
	tegra_sor_writel(sor, 0, SOR_INT_ENABLE);

	tegra_output_exit(&sor->output);

	if (sor->aux) {
		err = drm_dp_aux_detach(sor->aux);
		if (err < 0) {
			dev_err(sor->dev, "failed to detach DP: %d\n", err);
			return err;
		}
	}

	clk_disable_unprepare(sor->clk_safe);
	clk_disable_unprepare(sor->clk_dp);
	clk_disable_unprepare(sor->clk);

	return 0;
}