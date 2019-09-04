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
typedef  int /*<<< orphan*/  u32 ;
struct mbox_chan {struct imx_mu_con_priv* con_priv; int /*<<< orphan*/  mbox; } ;
struct imx_mu_priv {int /*<<< orphan*/  dev; } ;
struct imx_mu_con_priv {int type; int /*<<< orphan*/  txdb_tasklet; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IMX_MU_TYPE_TX 129 
#define  IMX_MU_TYPE_TXDB 128 
 int /*<<< orphan*/  IMX_MU_xCR_GIRn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMX_MU_xCR_TIEn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMX_MU_xTRn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  imx_mu_write (struct imx_mu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_mu_xcr_rmw (struct imx_mu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct imx_mu_priv* to_imx_mu_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_mu_send_data(struct mbox_chan *chan, void *data)
{
	struct imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	struct imx_mu_con_priv *cp = chan->con_priv;
	u32 *arg = data;

	switch (cp->type) {
	case IMX_MU_TYPE_TX:
		imx_mu_write(priv, *arg, IMX_MU_xTRn(cp->idx));
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_TIEn(cp->idx), 0);
		break;
	case IMX_MU_TYPE_TXDB:
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_GIRn(cp->idx), 0);
		tasklet_schedule(&cp->txdb_tasklet);
		break;
	default:
		dev_warn_ratelimited(priv->dev, "Send data on wrong channel type: %d\n", cp->type);
		return -EINVAL;
	}

	return 0;
}