#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct vc4_exec_info {scalar_t__ seqno; } ;
struct vc4_dev {int /*<<< orphan*/  job_lock; int /*<<< orphan*/  bin_alloc_used; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ENOMEM ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_exec_info* vc4_last_render_job (struct vc4_dev*) ; 
 int vc4_wait_for_seqno (struct drm_device*,scalar_t__,unsigned long long,int) ; 

int vc4_v3d_get_bin_slot(struct vc4_dev *vc4)
{
	struct drm_device *dev = vc4->dev;
	unsigned long irqflags;
	int slot;
	uint64_t seqno = 0;
	struct vc4_exec_info *exec;

try_again:
	spin_lock_irqsave(&vc4->job_lock, irqflags);
	slot = ffs(~vc4->bin_alloc_used);
	if (slot != 0) {
		/* Switch from ffs() bit index to a 0-based index. */
		slot--;
		vc4->bin_alloc_used |= BIT(slot);
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		return slot;
	}

	/* Couldn't find an open slot.  Wait for render to complete
	 * and try again.
	 */
	exec = vc4_last_render_job(vc4);
	if (exec)
		seqno = exec->seqno;
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	if (seqno) {
		int ret = vc4_wait_for_seqno(dev, seqno, ~0ull, true);

		if (ret == 0)
			goto try_again;

		return ret;
	}

	return -ENOMEM;
}