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
struct imx_mu_priv {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct imx_mu_con_priv {int type; int /*<<< orphan*/  idx; int /*<<< orphan*/  irq_desc; int /*<<< orphan*/  txdb_tasklet; } ;

/* Variables and functions */
#define  IMX_MU_TYPE_RX 129 
#define  IMX_MU_TYPE_RXDB 128 
 int IMX_MU_TYPE_TXDB ; 
 int /*<<< orphan*/  IMX_MU_xCR_GIEn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMX_MU_xCR_RIEn (int /*<<< orphan*/ ) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_mu_isr ; 
 int /*<<< orphan*/  imx_mu_txdb_tasklet ; 
 int /*<<< orphan*/  imx_mu_xcr_rmw (struct imx_mu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mbox_chan*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct imx_mu_priv* to_imx_mu_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_mu_startup(struct mbox_chan *chan)
{
	struct imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	struct imx_mu_con_priv *cp = chan->con_priv;
	int ret;

	if (cp->type == IMX_MU_TYPE_TXDB) {
		/* Tx doorbell don't have ACK support */
		tasklet_init(&cp->txdb_tasklet, imx_mu_txdb_tasklet,
			     (unsigned long)cp);
		return 0;
	}

	ret = request_irq(priv->irq, imx_mu_isr, IRQF_SHARED |
			  IRQF_NO_SUSPEND, cp->irq_desc, chan);
	if (ret) {
		dev_err(priv->dev,
			"Unable to acquire IRQ %d\n", priv->irq);
		return ret;
	}

	switch (cp->type) {
	case IMX_MU_TYPE_RX:
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_RIEn(cp->idx), 0);
		break;
	case IMX_MU_TYPE_RXDB:
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_GIEn(cp->idx), 0);
		break;
	default:
		break;
	}

	return 0;
}