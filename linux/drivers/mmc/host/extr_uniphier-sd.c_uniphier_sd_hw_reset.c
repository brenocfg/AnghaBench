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
struct uniphier_sd_priv {int /*<<< orphan*/  rst_hw; } ;
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void uniphier_sd_hw_reset(struct tmio_mmc_host *host)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);

	reset_control_assert(priv->rst_hw);
	/* For eMMC, minimum is 1us but give it 9us for good measure */
	udelay(9);
	reset_control_deassert(priv->rst_hw);
	/* For eMMC, minimum is 200us but give it 300us for good measure */
	usleep_range(300, 1000);
}