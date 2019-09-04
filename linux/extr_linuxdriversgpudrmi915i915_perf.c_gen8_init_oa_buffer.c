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
typedef  int u32 ;
struct TYPE_6__ {int head; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  ptr_lock; int /*<<< orphan*/  last_ctx_id; TYPE_1__* tails; int /*<<< orphan*/  vma; } ;
struct TYPE_7__ {int pollin; TYPE_2__ oa_buffer; } ;
struct TYPE_8__ {TYPE_3__ oa; } ;
struct drm_i915_private {TYPE_4__ perf; } ;
struct TYPE_5__ {void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_OABUFFER ; 
 int GEN8_OABUFFER_MEM_SELECT_GGTT ; 
 int /*<<< orphan*/  GEN8_OABUFFER_UDW ; 
 int /*<<< orphan*/  GEN8_OAHEADPTR ; 
 int /*<<< orphan*/  GEN8_OASTATUS ; 
 int /*<<< orphan*/  GEN8_OATAILPTR ; 
 int GEN8_OATAILPTR_MASK ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INVALID_CTX_ID ; 
 void* INVALID_TAIL_PTR ; 
 int OABUFFER_SIZE_16M ; 
 int /*<<< orphan*/  OA_BUFFER_SIZE ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gen8_init_oa_buffer(struct drm_i915_private *dev_priv)
{
	u32 gtt_offset = i915_ggtt_offset(dev_priv->perf.oa.oa_buffer.vma);
	unsigned long flags;

	spin_lock_irqsave(&dev_priv->perf.oa.oa_buffer.ptr_lock, flags);

	I915_WRITE(GEN8_OASTATUS, 0);
	I915_WRITE(GEN8_OAHEADPTR, gtt_offset);
	dev_priv->perf.oa.oa_buffer.head = gtt_offset;

	I915_WRITE(GEN8_OABUFFER_UDW, 0);

	/*
	 * PRM says:
	 *
	 *  "This MMIO must be set before the OATAILPTR
	 *  register and after the OAHEADPTR register. This is
	 *  to enable proper functionality of the overflow
	 *  bit."
	 */
	I915_WRITE(GEN8_OABUFFER, gtt_offset |
		   OABUFFER_SIZE_16M | GEN8_OABUFFER_MEM_SELECT_GGTT);
	I915_WRITE(GEN8_OATAILPTR, gtt_offset & GEN8_OATAILPTR_MASK);

	/* Mark that we need updated tail pointers to read from... */
	dev_priv->perf.oa.oa_buffer.tails[0].offset = INVALID_TAIL_PTR;
	dev_priv->perf.oa.oa_buffer.tails[1].offset = INVALID_TAIL_PTR;

	/*
	 * Reset state used to recognise context switches, affecting which
	 * reports we will forward to userspace while filtering for a single
	 * context.
	 */
	dev_priv->perf.oa.oa_buffer.last_ctx_id = INVALID_CTX_ID;

	spin_unlock_irqrestore(&dev_priv->perf.oa.oa_buffer.ptr_lock, flags);

	/*
	 * NB: although the OA buffer will initially be allocated
	 * zeroed via shmfs (and so this memset is redundant when
	 * first allocating), we may re-init the OA buffer, either
	 * when re-enabling a stream or in error/reset paths.
	 *
	 * The reason we clear the buffer for each re-init is for the
	 * sanity check in gen8_append_oa_reports() that looks at the
	 * reason field to make sure it's non-zero which relies on
	 * the assumption that new reports are being written to zeroed
	 * memory...
	 */
	memset(dev_priv->perf.oa.oa_buffer.vaddr, 0, OA_BUFFER_SIZE);

	/*
	 * Maybe make ->pollin per-stream state if we support multiple
	 * concurrent streams in the future.
	 */
	dev_priv->perf.oa.pollin = false;
}