#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct prp_priv {int /*<<< orphan*/  csi_id; TYPE_1__* src_sd; struct imx_ic_priv* ic_priv; } ;
struct imx_ic_priv {int /*<<< orphan*/  ipu; } ;
struct TYPE_2__ {int grp_id; } ;

/* Variables and functions */
 int IMX_MEDIA_GRP_ID_IPU_VDIC ; 
 int /*<<< orphan*/  ipu_set_ic_src_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prp_start(struct prp_priv *priv)
{
	struct imx_ic_priv *ic_priv = priv->ic_priv;
	bool src_is_vdic;

	/* set IC to receive from CSI or VDI depending on source */
	src_is_vdic = !!(priv->src_sd->grp_id & IMX_MEDIA_GRP_ID_IPU_VDIC);

	ipu_set_ic_src_mux(ic_priv->ipu, priv->csi_id, src_is_vdic);

	return 0;
}