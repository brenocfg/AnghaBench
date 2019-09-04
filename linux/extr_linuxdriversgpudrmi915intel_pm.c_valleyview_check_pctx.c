#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long start; } ;
struct drm_i915_private {TYPE_3__* vlv_pctx; TYPE_1__ dsm; } ;
struct TYPE_6__ {TYPE_2__* stolen; } ;
struct TYPE_5__ {unsigned long start; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_PCBR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void valleyview_check_pctx(struct drm_i915_private *dev_priv)
{
	unsigned long pctx_addr = I915_READ(VLV_PCBR) & ~4095;

	WARN_ON(pctx_addr != dev_priv->dsm.start +
			     dev_priv->vlv_pctx->stolen->start);
}