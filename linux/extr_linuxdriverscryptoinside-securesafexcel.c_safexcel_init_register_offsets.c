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
struct safexcel_register_offsets {int /*<<< orphan*/  pe; int /*<<< orphan*/  hia_gen_cfg; int /*<<< orphan*/  hia_dse_thr; int /*<<< orphan*/  hia_dse; int /*<<< orphan*/  hia_dfe_thr; int /*<<< orphan*/  hia_dfe; int /*<<< orphan*/  hia_aic_xdr; int /*<<< orphan*/  hia_aic_r; int /*<<< orphan*/  hia_aic_g; int /*<<< orphan*/  hia_aic; } ;
struct safexcel_crypto_priv {int version; struct safexcel_register_offsets offsets; } ;

/* Variables and functions */
#define  EIP197B 130 
#define  EIP197D 129 
 int /*<<< orphan*/  EIP197_HIA_AIC_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_AIC_G_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_AIC_R_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_AIC_xDR_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_DFE_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_DFE_THR_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_DSE_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_DSE_THR_BASE ; 
 int /*<<< orphan*/  EIP197_HIA_GEN_CFG_BASE ; 
 int /*<<< orphan*/  EIP197_PE_BASE ; 
#define  EIP97IES 128 
 int /*<<< orphan*/  EIP97_HIA_AIC_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_AIC_G_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_AIC_R_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_AIC_xDR_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_DFE_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_DFE_THR_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_DSE_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_DSE_THR_BASE ; 
 int /*<<< orphan*/  EIP97_HIA_GEN_CFG_BASE ; 
 int /*<<< orphan*/  EIP97_PE_BASE ; 

__attribute__((used)) static void safexcel_init_register_offsets(struct safexcel_crypto_priv *priv)
{
	struct safexcel_register_offsets *offsets = &priv->offsets;

	switch (priv->version) {
	case EIP197B:
	case EIP197D:
		offsets->hia_aic	= EIP197_HIA_AIC_BASE;
		offsets->hia_aic_g	= EIP197_HIA_AIC_G_BASE;
		offsets->hia_aic_r	= EIP197_HIA_AIC_R_BASE;
		offsets->hia_aic_xdr	= EIP197_HIA_AIC_xDR_BASE;
		offsets->hia_dfe	= EIP197_HIA_DFE_BASE;
		offsets->hia_dfe_thr	= EIP197_HIA_DFE_THR_BASE;
		offsets->hia_dse	= EIP197_HIA_DSE_BASE;
		offsets->hia_dse_thr	= EIP197_HIA_DSE_THR_BASE;
		offsets->hia_gen_cfg	= EIP197_HIA_GEN_CFG_BASE;
		offsets->pe		= EIP197_PE_BASE;
		break;
	case EIP97IES:
		offsets->hia_aic	= EIP97_HIA_AIC_BASE;
		offsets->hia_aic_g	= EIP97_HIA_AIC_G_BASE;
		offsets->hia_aic_r	= EIP97_HIA_AIC_R_BASE;
		offsets->hia_aic_xdr	= EIP97_HIA_AIC_xDR_BASE;
		offsets->hia_dfe	= EIP97_HIA_DFE_BASE;
		offsets->hia_dfe_thr	= EIP97_HIA_DFE_THR_BASE;
		offsets->hia_dse	= EIP97_HIA_DSE_BASE;
		offsets->hia_dse_thr	= EIP97_HIA_DSE_THR_BASE;
		offsets->hia_gen_cfg	= EIP97_HIA_GEN_CFG_BASE;
		offsets->pe		= EIP97_PE_BASE;
		break;
	}
}