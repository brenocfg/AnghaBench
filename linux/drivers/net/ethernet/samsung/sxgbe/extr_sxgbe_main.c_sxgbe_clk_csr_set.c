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
typedef  scalar_t__ u32 ;
struct sxgbe_priv_data {int /*<<< orphan*/  clk_csr; int /*<<< orphan*/  sxgbe_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_CSR_100_150M ; 
 int /*<<< orphan*/  SXGBE_CSR_150_250M ; 
 int /*<<< orphan*/  SXGBE_CSR_250_300M ; 
 int /*<<< orphan*/  SXGBE_CSR_300_350M ; 
 int /*<<< orphan*/  SXGBE_CSR_350_400M ; 
 int /*<<< orphan*/  SXGBE_CSR_400_500M ; 
 scalar_t__ SXGBE_CSR_F_150M ; 
 scalar_t__ SXGBE_CSR_F_250M ; 
 scalar_t__ SXGBE_CSR_F_300M ; 
 scalar_t__ SXGBE_CSR_F_350M ; 
 scalar_t__ SXGBE_CSR_F_400M ; 
 scalar_t__ SXGBE_CSR_F_500M ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sxgbe_clk_csr_set(struct sxgbe_priv_data *priv)
{
	u32 clk_rate = clk_get_rate(priv->sxgbe_clk);

	/* assign the proper divider, this will be used during
	 * mdio communication
	 */
	if (clk_rate < SXGBE_CSR_F_150M)
		priv->clk_csr = SXGBE_CSR_100_150M;
	else if (clk_rate <= SXGBE_CSR_F_250M)
		priv->clk_csr = SXGBE_CSR_150_250M;
	else if (clk_rate <= SXGBE_CSR_F_300M)
		priv->clk_csr = SXGBE_CSR_250_300M;
	else if (clk_rate <= SXGBE_CSR_F_350M)
		priv->clk_csr = SXGBE_CSR_300_350M;
	else if (clk_rate <= SXGBE_CSR_F_400M)
		priv->clk_csr = SXGBE_CSR_350_400M;
	else if (clk_rate <= SXGBE_CSR_F_500M)
		priv->clk_csr = SXGBE_CSR_400_500M;
}