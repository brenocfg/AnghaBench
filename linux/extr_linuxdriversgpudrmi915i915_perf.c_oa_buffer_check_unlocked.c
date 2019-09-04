#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct i915_vma {int dummy; } ;
struct TYPE_8__ {int format_size; int head; unsigned int aged_tail_idx; scalar_t__ aging_timestamp; int /*<<< orphan*/  ptr_lock; TYPE_2__* tails; struct i915_vma* vma; } ;
struct TYPE_6__ {int (* oa_hw_tail_read ) (struct drm_i915_private*) ;} ;
struct TYPE_9__ {TYPE_3__ oa_buffer; TYPE_1__ ops; } ;
struct TYPE_10__ {TYPE_4__ oa; } ;
struct drm_i915_private {TYPE_5__ perf; } ;
struct TYPE_7__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int INVALID_TAIL_PTR ; 
 int OA_BUFFER_SIZE ; 
 scalar_t__ OA_TAIL_MARGIN_NSEC ; 
 int OA_TAKEN (int,int) ; 
 int i915_ggtt_offset (struct i915_vma*) ; 
 scalar_t__ ktime_get_mono_fast_ns () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct drm_i915_private*) ; 

__attribute__((used)) static bool oa_buffer_check_unlocked(struct drm_i915_private *dev_priv)
{
	int report_size = dev_priv->perf.oa.oa_buffer.format_size;
	unsigned long flags;
	unsigned int aged_idx;
	u32 head, hw_tail, aged_tail, aging_tail;
	u64 now;

	/* We have to consider the (unlikely) possibility that read() errors
	 * could result in an OA buffer reset which might reset the head,
	 * tails[] and aged_tail state.
	 */
	spin_lock_irqsave(&dev_priv->perf.oa.oa_buffer.ptr_lock, flags);

	/* NB: The head we observe here might effectively be a little out of
	 * date (between head and tails[aged_idx].offset if there is currently
	 * a read() in progress.
	 */
	head = dev_priv->perf.oa.oa_buffer.head;

	aged_idx = dev_priv->perf.oa.oa_buffer.aged_tail_idx;
	aged_tail = dev_priv->perf.oa.oa_buffer.tails[aged_idx].offset;
	aging_tail = dev_priv->perf.oa.oa_buffer.tails[!aged_idx].offset;

	hw_tail = dev_priv->perf.oa.ops.oa_hw_tail_read(dev_priv);

	/* The tail pointer increases in 64 byte increments,
	 * not in report_size steps...
	 */
	hw_tail &= ~(report_size - 1);

	now = ktime_get_mono_fast_ns();

	/* Update the aged tail
	 *
	 * Flip the tail pointer available for read()s once the aging tail is
	 * old enough to trust that the corresponding data will be visible to
	 * the CPU...
	 *
	 * Do this before updating the aging pointer in case we may be able to
	 * immediately start aging a new pointer too (if new data has become
	 * available) without needing to wait for a later hrtimer callback.
	 */
	if (aging_tail != INVALID_TAIL_PTR &&
	    ((now - dev_priv->perf.oa.oa_buffer.aging_timestamp) >
	     OA_TAIL_MARGIN_NSEC)) {

		aged_idx ^= 1;
		dev_priv->perf.oa.oa_buffer.aged_tail_idx = aged_idx;

		aged_tail = aging_tail;

		/* Mark that we need a new pointer to start aging... */
		dev_priv->perf.oa.oa_buffer.tails[!aged_idx].offset = INVALID_TAIL_PTR;
		aging_tail = INVALID_TAIL_PTR;
	}

	/* Update the aging tail
	 *
	 * We throttle aging tail updates until we have a new tail that
	 * represents >= one report more data than is already available for
	 * reading. This ensures there will be enough data for a successful
	 * read once this new pointer has aged and ensures we will give the new
	 * pointer time to age.
	 */
	if (aging_tail == INVALID_TAIL_PTR &&
	    (aged_tail == INVALID_TAIL_PTR ||
	     OA_TAKEN(hw_tail, aged_tail) >= report_size)) {
		struct i915_vma *vma = dev_priv->perf.oa.oa_buffer.vma;
		u32 gtt_offset = i915_ggtt_offset(vma);

		/* Be paranoid and do a bounds check on the pointer read back
		 * from hardware, just in case some spurious hardware condition
		 * could put the tail out of bounds...
		 */
		if (hw_tail >= gtt_offset &&
		    hw_tail < (gtt_offset + OA_BUFFER_SIZE)) {
			dev_priv->perf.oa.oa_buffer.tails[!aged_idx].offset =
				aging_tail = hw_tail;
			dev_priv->perf.oa.oa_buffer.aging_timestamp = now;
		} else {
			DRM_ERROR("Ignoring spurious out of range OA buffer tail pointer = %u\n",
				  hw_tail);
		}
	}

	spin_unlock_irqrestore(&dev_priv->perf.oa.oa_buffer.ptr_lock, flags);

	return aged_tail == INVALID_TAIL_PTR ?
		false : OA_TAKEN(aged_tail, head) >= report_size;
}