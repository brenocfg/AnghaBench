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
struct mbox_chan {struct imx_mu_con_priv* con_priv; int /*<<< orphan*/  mbox; } ;
struct imx_mu_priv {int /*<<< orphan*/  irq; } ;
struct imx_mu_con_priv {scalar_t__ type; int /*<<< orphan*/  idx; int /*<<< orphan*/  txdb_tasklet; } ;

/* Variables and functions */
 scalar_t__ IMX_MU_TYPE_TXDB ; 
 int IMX_MU_xCR_GIEn (int /*<<< orphan*/ ) ; 
 int IMX_MU_xCR_RIEn (int /*<<< orphan*/ ) ; 
 int IMX_MU_xCR_TIEn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mbox_chan*) ; 
 int /*<<< orphan*/  imx_mu_xcr_rmw (struct imx_mu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct imx_mu_priv* to_imx_mu_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_mu_shutdown(struct mbox_chan *chan)
{
	struct imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	struct imx_mu_con_priv *cp = chan->con_priv;

	if (cp->type == IMX_MU_TYPE_TXDB)
		tasklet_kill(&cp->txdb_tasklet);

	imx_mu_xcr_rmw(priv, 0, IMX_MU_xCR_TIEn(cp->idx) |
		       IMX_MU_xCR_RIEn(cp->idx) | IMX_MU_xCR_GIEn(cp->idx));

	free_irq(priv->irq, chan);
}