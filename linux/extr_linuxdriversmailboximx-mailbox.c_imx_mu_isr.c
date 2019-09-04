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
struct mbox_chan {struct imx_mu_con_priv* con_priv; int /*<<< orphan*/  mbox; } ;
struct imx_mu_priv {int /*<<< orphan*/  dev; } ;
struct imx_mu_con_priv {int type; int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
#define  IMX_MU_TYPE_RX 130 
#define  IMX_MU_TYPE_RXDB 129 
#define  IMX_MU_TYPE_TX 128 
 int /*<<< orphan*/  IMX_MU_xCR ; 
 scalar_t__ IMX_MU_xCR_GIEn (int /*<<< orphan*/ ) ; 
 scalar_t__ IMX_MU_xCR_RIEn (int /*<<< orphan*/ ) ; 
 scalar_t__ IMX_MU_xCR_TIEn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMX_MU_xRRn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMX_MU_xSR ; 
 scalar_t__ IMX_MU_xSR_GIPn (int /*<<< orphan*/ ) ; 
 scalar_t__ IMX_MU_xSR_RFn (int /*<<< orphan*/ ) ; 
 scalar_t__ IMX_MU_xSR_TEn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ imx_mu_read (struct imx_mu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_mu_write (struct imx_mu_priv*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_mu_xcr_rmw (struct imx_mu_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mbox_chan_received_data (struct mbox_chan*,void*) ; 
 int /*<<< orphan*/  mbox_chan_txdone (struct mbox_chan*,int /*<<< orphan*/ ) ; 
 struct imx_mu_priv* to_imx_mu_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t imx_mu_isr(int irq, void *p)
{
	struct mbox_chan *chan = p;
	struct imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	struct imx_mu_con_priv *cp = chan->con_priv;
	u32 val, ctrl, dat;

	ctrl = imx_mu_read(priv, IMX_MU_xCR);
	val = imx_mu_read(priv, IMX_MU_xSR);

	switch (cp->type) {
	case IMX_MU_TYPE_TX:
		val &= IMX_MU_xSR_TEn(cp->idx) &
			(ctrl & IMX_MU_xCR_TIEn(cp->idx));
		break;
	case IMX_MU_TYPE_RX:
		val &= IMX_MU_xSR_RFn(cp->idx) &
			(ctrl & IMX_MU_xCR_RIEn(cp->idx));
		break;
	case IMX_MU_TYPE_RXDB:
		val &= IMX_MU_xSR_GIPn(cp->idx) &
			(ctrl & IMX_MU_xCR_GIEn(cp->idx));
		break;
	default:
		break;
	}

	if (!val)
		return IRQ_NONE;

	if (val == IMX_MU_xSR_TEn(cp->idx)) {
		imx_mu_xcr_rmw(priv, 0, IMX_MU_xCR_TIEn(cp->idx));
		mbox_chan_txdone(chan, 0);
	} else if (val == IMX_MU_xSR_RFn(cp->idx)) {
		dat = imx_mu_read(priv, IMX_MU_xRRn(cp->idx));
		mbox_chan_received_data(chan, (void *)&dat);
	} else if (val == IMX_MU_xSR_GIPn(cp->idx)) {
		imx_mu_write(priv, IMX_MU_xSR_GIPn(cp->idx), IMX_MU_xSR);
		mbox_chan_received_data(chan, NULL);
	} else {
		dev_warn_ratelimited(priv->dev, "Not handled interrupt\n");
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}