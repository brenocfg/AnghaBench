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
struct opregion_asle {int tche; int ardy; } ;
struct TYPE_2__ {struct opregion_asle* asle; } ;
struct drm_psb_private {TYPE_1__ opregion; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int ASLE_ALS_EN ; 
 int ASLE_BLC_EN ; 
 int ASLE_PFIT_EN ; 
 int ASLE_PFMB_EN ; 
 int /*<<< orphan*/  PIPE_LEGACY_BLC_EVENT_ENABLE ; 
 int /*<<< orphan*/  psb_enable_pipestat (struct drm_psb_private*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ system_opregion ; 

void psb_intel_opregion_enable_asle(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct opregion_asle *asle = dev_priv->opregion.asle;

	if (asle && system_opregion ) {
		/* Don't do this on Medfield or other non PC like devices, they
		   use the bit for something different altogether */
		psb_enable_pipestat(dev_priv, 0, PIPE_LEGACY_BLC_EVENT_ENABLE);
		psb_enable_pipestat(dev_priv, 1, PIPE_LEGACY_BLC_EVENT_ENABLE);

		asle->tche = ASLE_ALS_EN | ASLE_BLC_EN | ASLE_PFIT_EN
								| ASLE_PFMB_EN;
		asle->ardy = 1;
	}
}