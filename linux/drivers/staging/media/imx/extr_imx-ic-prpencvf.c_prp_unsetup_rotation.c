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
struct prp_priv {int /*<<< orphan*/ * rot_buf; int /*<<< orphan*/  ic; int /*<<< orphan*/  rot_in_ch; int /*<<< orphan*/  out_ch; int /*<<< orphan*/  rot_out_ch; struct imx_ic_priv* ic_priv; } ;
struct imx_ic_priv {int /*<<< orphan*/  ipu_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_free_dma_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_ic_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_task_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_disable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_unlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prp_unsetup_rotation(struct prp_priv *priv)
{
	struct imx_ic_priv *ic_priv = priv->ic_priv;

	ipu_ic_task_disable(priv->ic);

	ipu_idmac_disable_channel(priv->out_ch);
	ipu_idmac_disable_channel(priv->rot_in_ch);
	ipu_idmac_disable_channel(priv->rot_out_ch);

	ipu_idmac_unlink(priv->out_ch, priv->rot_in_ch);

	ipu_ic_disable(priv->ic);

	imx_media_free_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[0]);
	imx_media_free_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[1]);
}