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
struct virt_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/ * vd_terminated; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_vdesc_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void vchan_synchronize(struct virt_dma_chan *vc)
{
	unsigned long flags;

	tasklet_kill(&vc->task);

	spin_lock_irqsave(&vc->lock, flags);
	if (vc->vd_terminated) {
		vchan_vdesc_fini(vc->vd_terminated);
		vc->vd_terminated = NULL;
	}
	spin_unlock_irqrestore(&vc->lock, flags);
}