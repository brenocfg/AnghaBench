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
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ tail; scalar_t__ last_flush; int space; int size; } ;
struct TYPE_6__ {int usec_timeout; int dma_access; TYPE_1__* primary; TYPE_3__ prim; } ;
typedef  TYPE_2__ drm_mga_private_t ;
typedef  TYPE_3__ drm_mga_primary_buffer_t ;
struct TYPE_5__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  MGA_DMAPAD ; 
 int MGA_ENDPRDMASTS ; 
 int MGA_ENGINE_IDLE_MASK ; 
 int /*<<< orphan*/  MGA_PRIMADDRESS ; 
 int /*<<< orphan*/  MGA_PRIMEND ; 
 int MGA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGA_STATUS ; 
 int /*<<< orphan*/  MGA_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mga_flush_write_combine () ; 
 int /*<<< orphan*/  udelay (int) ; 

void mga_do_dma_flush(drm_mga_private_t *dev_priv)
{
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	u32 head, tail;
	u32 status = 0;
	int i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	/* We need to wait so that we can do an safe flush */
	for (i = 0; i < dev_priv->usec_timeout; i++) {
		status = MGA_READ(MGA_STATUS) & MGA_ENGINE_IDLE_MASK;
		if (status == MGA_ENDPRDMASTS)
			break;
		udelay(1);
	}

	if (primary->tail == primary->last_flush) {
		DRM_DEBUG("   bailing out...\n");
		return;
	}

	tail = primary->tail + dev_priv->primary->offset;

	/* We need to pad the stream between flushes, as the card
	 * actually (partially?) reads the first of these commands.
	 * See page 4-16 in the G400 manual, middle of the page or so.
	 */
	BEGIN_DMA(1);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();

	primary->last_flush = primary->tail;

	head = MGA_READ(MGA_PRIMADDRESS);

	if (head <= tail)
		primary->space = primary->size - primary->tail;
	else
		primary->space = head - tail;

	DRM_DEBUG("   head = 0x%06lx\n", (unsigned long)(head - dev_priv->primary->offset));
	DRM_DEBUG("   tail = 0x%06lx\n", (unsigned long)(tail - dev_priv->primary->offset));
	DRM_DEBUG("  space = 0x%06x\n", primary->space);

	mga_flush_write_combine();
	MGA_WRITE(MGA_PRIMEND, tail | dev_priv->dma_access);

	DRM_DEBUG("done.\n");
}