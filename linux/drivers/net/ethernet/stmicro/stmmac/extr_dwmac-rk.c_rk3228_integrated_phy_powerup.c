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
struct rk_priv_data {int /*<<< orphan*/  grf; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK3228_GRF_CON_MUX ; 
 int /*<<< orphan*/  RK3228_GRF_CON_MUX_GMAC_INTEGRATED_PHY ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk3228_integrated_phy_powerup(struct rk_priv_data *priv)
{
	regmap_write(priv->grf, RK3228_GRF_CON_MUX,
		     RK3228_GRF_CON_MUX_GMAC_INTEGRATED_PHY);
}