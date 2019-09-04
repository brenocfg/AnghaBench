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
typedef  int /*<<< orphan*/  u32 ;
struct gtt_range {scalar_t__ offset; } ;
struct gma_crtc {size_t pipe; struct gtt_range* cursor_gt; scalar_t__ cursor_addr; } ;
struct drm_psb_private {scalar_t__ stolen_base; TYPE_1__* ops; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {scalar_t__ cursor_needs_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURABASE ; 
 int /*<<< orphan*/  CURACNTR ; 
 int /*<<< orphan*/  CURBBASE ; 
 int /*<<< orphan*/  CURBCNTR ; 
 int /*<<< orphan*/  CURCBASE ; 
 int /*<<< orphan*/  CURCCNTR ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gtt_range* psb_gtt_alloc_range (struct drm_device*,int,char*,int,int) ; 

__attribute__((used)) static void psb_intel_cursor_init(struct drm_device *dev,
				  struct gma_crtc *gma_crtc)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 control[3] = { CURACNTR, CURBCNTR, CURCCNTR };
	u32 base[3] = { CURABASE, CURBBASE, CURCBASE };
	struct gtt_range *cursor_gt;

	if (dev_priv->ops->cursor_needs_phys) {
		/* Allocate 4 pages of stolen mem for a hardware cursor. That
		 * is enough for the 64 x 64 ARGB cursors we support.
		 */
		cursor_gt = psb_gtt_alloc_range(dev, 4 * PAGE_SIZE, "cursor", 1,
						PAGE_SIZE);
		if (!cursor_gt) {
			gma_crtc->cursor_gt = NULL;
			goto out;
		}
		gma_crtc->cursor_gt = cursor_gt;
		gma_crtc->cursor_addr = dev_priv->stolen_base +
							cursor_gt->offset;
	} else {
		gma_crtc->cursor_gt = NULL;
	}

out:
	REG_WRITE(control[gma_crtc->pipe], 0);
	REG_WRITE(base[gma_crtc->pipe], 0);
}