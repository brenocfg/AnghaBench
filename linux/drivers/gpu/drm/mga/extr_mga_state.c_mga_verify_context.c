#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dstorg; } ;
struct TYPE_5__ {TYPE_3__ context_state; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_6__ {scalar_t__ front_offset; scalar_t__ back_offset; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
typedef  TYPE_3__ drm_mga_context_regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int EINVAL ; 

__attribute__((used)) static int mga_verify_context(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;

	if (ctx->dstorg != dev_priv->front_offset &&
	    ctx->dstorg != dev_priv->back_offset) {
		DRM_ERROR("*** bad DSTORG: %x (front %x, back %x)\n\n",
			  ctx->dstorg, dev_priv->front_offset,
			  dev_priv->back_offset);
		ctx->dstorg = 0;
		return -EINVAL;
	}

	return 0;
}