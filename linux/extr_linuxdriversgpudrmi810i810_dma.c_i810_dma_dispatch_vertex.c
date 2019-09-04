#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct drm_device {TYPE_1__* agp; TYPE_3__* dev_private; } ;
struct drm_clip_rect {int x1; int y1; int x2; int y2; } ;
struct drm_buf {scalar_t__ bus_address; TYPE_4__* dev_private; } ;
struct TYPE_6__ {int nbox; unsigned int vertex_prim; scalar_t__ dirty; struct drm_clip_rect* boxes; } ;
typedef  TYPE_2__ drm_i810_sarea_t ;
struct TYPE_7__ {int counter; TYPE_2__* sarea_priv; } ;
typedef  TYPE_3__ drm_i810_private_t ;
struct TYPE_8__ {scalar_t__ currently_mapped; int my_use_idx; int /*<<< orphan*/  in_use; scalar_t__ kernel_virtual; } ;
typedef  TYPE_4__ drm_i810_buf_priv_t ;
struct TYPE_5__ {unsigned long base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_LP_RING () ; 
 unsigned long BB1_PROTECTED ; 
 int /*<<< orphan*/  BEGIN_LP_RING (int) ; 
 int CMD_OP_BATCH_BUFFER ; 
 int CMD_REPORT_HEAD ; 
 int CMD_STORE_DWORD_IDX ; 
 unsigned int GFX_OP_PRIMITIVE ; 
 int GFX_OP_SCISSOR ; 
 int GFX_OP_SCISSOR_INFO ; 
 int /*<<< orphan*/  I810_BUF_CLIENT ; 
 int I810_BUF_FREE ; 
 int /*<<< orphan*/  I810_BUF_HARDWARE ; 
 scalar_t__ I810_BUF_MAPPED ; 
 int I810_NR_SAREA_CLIPRECTS ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 unsigned int PR_MASK ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int SC_ENABLE ; 
 int SC_UPDATE_SCISSOR ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i810EmitState (struct drm_device*) ; 
 int /*<<< orphan*/  i810_kernel_lost_context (struct drm_device*) ; 
 int /*<<< orphan*/  i810_unmap_buffer (struct drm_buf*) ; 

__attribute__((used)) static void i810_dma_dispatch_vertex(struct drm_device *dev,
				     struct drm_buf *buf, int discard, int used)
{
	drm_i810_private_t *dev_priv = dev->dev_private;
	drm_i810_buf_priv_t *buf_priv = buf->dev_private;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	struct drm_clip_rect *box = sarea_priv->boxes;
	int nbox = sarea_priv->nbox;
	unsigned long address = (unsigned long)buf->bus_address;
	unsigned long start = address - dev->agp->base;
	int i = 0;
	RING_LOCALS;

	i810_kernel_lost_context(dev);

	if (nbox > I810_NR_SAREA_CLIPRECTS)
		nbox = I810_NR_SAREA_CLIPRECTS;

	if (used > 4 * 1024)
		used = 0;

	if (sarea_priv->dirty)
		i810EmitState(dev);

	if (buf_priv->currently_mapped == I810_BUF_MAPPED) {
		unsigned int prim = (sarea_priv->vertex_prim & PR_MASK);

		*(u32 *) buf_priv->kernel_virtual =
		    ((GFX_OP_PRIMITIVE | prim | ((used / 4) - 2)));

		if (used & 4) {
			*(u32 *) ((char *) buf_priv->kernel_virtual + used) = 0;
			used += 4;
		}

		i810_unmap_buffer(buf);
	}

	if (used) {
		do {
			if (i < nbox) {
				BEGIN_LP_RING(4);
				OUT_RING(GFX_OP_SCISSOR | SC_UPDATE_SCISSOR |
					 SC_ENABLE);
				OUT_RING(GFX_OP_SCISSOR_INFO);
				OUT_RING(box[i].x1 | (box[i].y1 << 16));
				OUT_RING((box[i].x2 -
					  1) | ((box[i].y2 - 1) << 16));
				ADVANCE_LP_RING();
			}

			BEGIN_LP_RING(4);
			OUT_RING(CMD_OP_BATCH_BUFFER);
			OUT_RING(start | BB1_PROTECTED);
			OUT_RING(start + used - 4);
			OUT_RING(0);
			ADVANCE_LP_RING();

		} while (++i < nbox);
	}

	if (discard) {
		dev_priv->counter++;

		(void)cmpxchg(buf_priv->in_use, I810_BUF_CLIENT,
			      I810_BUF_HARDWARE);

		BEGIN_LP_RING(8);
		OUT_RING(CMD_STORE_DWORD_IDX);
		OUT_RING(20);
		OUT_RING(dev_priv->counter);
		OUT_RING(CMD_STORE_DWORD_IDX);
		OUT_RING(buf_priv->my_use_idx);
		OUT_RING(I810_BUF_FREE);
		OUT_RING(CMD_REPORT_HEAD);
		OUT_RING(0);
		ADVANCE_LP_RING();
	}
}