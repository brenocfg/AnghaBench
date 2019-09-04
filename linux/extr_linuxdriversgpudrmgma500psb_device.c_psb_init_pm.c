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
typedef  int u32 ;
struct drm_psb_private {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSB_CR_CLKGATECTL ; 
 int PSB_RSGX32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WSGX32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psb_init_pm(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	u32 gating = PSB_RSGX32(PSB_CR_CLKGATECTL);
	gating &= ~3;	/* Disable 2D clock gating */
	gating |= 1;
	PSB_WSGX32(gating, PSB_CR_CLKGATECTL);
	PSB_RSGX32(PSB_CR_CLKGATECTL);
}