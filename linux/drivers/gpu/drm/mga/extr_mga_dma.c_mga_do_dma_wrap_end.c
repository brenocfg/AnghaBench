#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  last_wrap; } ;
typedef  TYPE_2__ drm_mga_sarea_t ;
struct TYPE_9__ {int /*<<< orphan*/  wrapped; } ;
struct TYPE_8__ {TYPE_1__* primary; TYPE_2__* sarea_priv; TYPE_4__ prim; } ;
typedef  TYPE_3__ drm_mga_private_t ;
typedef  TYPE_4__ drm_mga_primary_buffer_t ;
struct TYPE_6__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int MGA_DMA_GENERAL ; 
 int /*<<< orphan*/  MGA_PRIMADDRESS ; 
 int /*<<< orphan*/  MGA_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mga_flush_write_combine () ; 

void mga_do_dma_wrap_end(drm_mga_private_t *dev_priv)
{
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	u32 head = dev_priv->primary->offset;
	DRM_DEBUG("\n");

	sarea_priv->last_wrap++;
	DRM_DEBUG("   wrap = %d\n", sarea_priv->last_wrap);

	mga_flush_write_combine();
	MGA_WRITE(MGA_PRIMADDRESS, head | MGA_DMA_GENERAL);

	clear_bit(0, &primary->wrapped);
	DRM_DEBUG("done.\n");
}