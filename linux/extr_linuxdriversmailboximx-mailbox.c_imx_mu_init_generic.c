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
struct imx_mu_priv {scalar_t__ side_b; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_MU_xCR ; 
 int /*<<< orphan*/  imx_mu_write (struct imx_mu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_mu_init_generic(struct imx_mu_priv *priv)
{
	if (priv->side_b)
		return;

	/* Set default MU configuration */
	imx_mu_write(priv, 0, IMX_MU_xCR);
}