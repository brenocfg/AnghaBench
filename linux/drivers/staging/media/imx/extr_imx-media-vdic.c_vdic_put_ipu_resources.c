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
struct vdic_priv {int /*<<< orphan*/ * vdi; int /*<<< orphan*/ * vdi_in_ch_n; int /*<<< orphan*/ * vdi_in_ch; int /*<<< orphan*/ * vdi_in_ch_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_idmac_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_vdi_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vdic_put_ipu_resources(struct vdic_priv *priv)
{
	if (priv->vdi_in_ch_p)
		ipu_idmac_put(priv->vdi_in_ch_p);
	priv->vdi_in_ch_p = NULL;

	if (priv->vdi_in_ch)
		ipu_idmac_put(priv->vdi_in_ch);
	priv->vdi_in_ch = NULL;

	if (priv->vdi_in_ch_n)
		ipu_idmac_put(priv->vdi_in_ch_n);
	priv->vdi_in_ch_n = NULL;

	if (!IS_ERR_OR_NULL(priv->vdi))
		ipu_vdi_put(priv->vdi);
	priv->vdi = NULL;
}