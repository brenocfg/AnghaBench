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
struct TYPE_5__ {scalar_t__ last_wrap; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_7__ {scalar_t__ last_flush; int /*<<< orphan*/  size; int /*<<< orphan*/  space; scalar_t__ tail; } ;
struct TYPE_6__ {TYPE_3__ prim; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
typedef  TYPE_3__ drm_mga_primary_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 

__attribute__((used)) static int mga_do_dma_reset(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;

	DRM_DEBUG("\n");

	/* The primary DMA stream should look like new right about now.
	 */
	primary->tail = 0;
	primary->space = primary->size;
	primary->last_flush = 0;

	sarea_priv->last_wrap = 0;

	/* FIXME: Reset counters, buffer ages etc...
	 */

	/* FIXME: What else do we need to reinitialize?  WARP stuff?
	 */

	return 0;
}