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
typedef  int u32 ;
struct TYPE_6__ {int head; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  ptr_lock; TYPE_1__* tails; int /*<<< orphan*/  vma; } ;
struct i915_perf_stream {int pollin; TYPE_3__ oa_buffer; struct drm_i915_private* dev_priv; } ;
struct TYPE_5__ {scalar_t__ gen7_latched_oastatus1; } ;
struct drm_i915_private {TYPE_2__ perf; } ;
struct TYPE_4__ {void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN7_OABUFFER ; 
 int /*<<< orphan*/  GEN7_OASTATUS1 ; 
 int /*<<< orphan*/  GEN7_OASTATUS2 ; 
 int GEN7_OASTATUS2_MEM_SELECT_GGTT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 void* INVALID_TAIL_PTR ; 
 int OABUFFER_SIZE_16M ; 
 int /*<<< orphan*/  OA_BUFFER_SIZE ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gen7_init_oa_buffer(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;
	u32 gtt_offset = i915_ggtt_offset(stream->oa_buffer.vma);
	unsigned long flags;

	spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

	/* Pre-DevBDW: OABUFFER must be set with counters off,
	 * before OASTATUS1, but after OASTATUS2
	 */
	I915_WRITE(GEN7_OASTATUS2,
		   gtt_offset | GEN7_OASTATUS2_MEM_SELECT_GGTT); /* head */
	stream->oa_buffer.head = gtt_offset;

	I915_WRITE(GEN7_OABUFFER, gtt_offset);

	I915_WRITE(GEN7_OASTATUS1, gtt_offset | OABUFFER_SIZE_16M); /* tail */

	/* Mark that we need updated tail pointers to read from... */
	stream->oa_buffer.tails[0].offset = INVALID_TAIL_PTR;
	stream->oa_buffer.tails[1].offset = INVALID_TAIL_PTR;

	spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);

	/* On Haswell we have to track which OASTATUS1 flags we've
	 * already seen since they can't be cleared while periodic
	 * sampling is enabled.
	 */
	dev_priv->perf.gen7_latched_oastatus1 = 0;

	/* NB: although the OA buffer will initially be allocated
	 * zeroed via shmfs (and so this memset is redundant when
	 * first allocating), we may re-init the OA buffer, either
	 * when re-enabling a stream or in error/reset paths.
	 *
	 * The reason we clear the buffer for each re-init is for the
	 * sanity check in gen7_append_oa_reports() that looks at the
	 * report-id field to make sure it's non-zero which relies on
	 * the assumption that new reports are being written to zeroed
	 * memory...
	 */
	memset(stream->oa_buffer.vaddr, 0, OA_BUFFER_SIZE);

	/* Maybe make ->pollin per-stream state if we support multiple
	 * concurrent streams in the future.
	 */
	stream->pollin = false;
}