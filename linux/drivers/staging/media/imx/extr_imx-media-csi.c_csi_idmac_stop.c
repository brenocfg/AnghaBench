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
struct csi_priv {int /*<<< orphan*/  eof_timeout_timer; int /*<<< orphan*/  underrun_buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  nfb4eof_irq; int /*<<< orphan*/  eof_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  csi_idmac_put_ipu_resources (struct csi_priv*) ; 
 int /*<<< orphan*/  csi_idmac_unsetup (struct csi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct csi_priv*) ; 
 int /*<<< orphan*/  imx_media_free_dma_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void csi_idmac_stop(struct csi_priv *priv)
{
	devm_free_irq(priv->dev, priv->eof_irq, priv);
	devm_free_irq(priv->dev, priv->nfb4eof_irq, priv);

	csi_idmac_unsetup(priv, VB2_BUF_STATE_ERROR);

	imx_media_free_dma_buf(priv->dev, &priv->underrun_buf);

	/* cancel the EOF timeout timer */
	del_timer_sync(&priv->eof_timeout_timer);

	csi_idmac_put_ipu_resources(priv);
}