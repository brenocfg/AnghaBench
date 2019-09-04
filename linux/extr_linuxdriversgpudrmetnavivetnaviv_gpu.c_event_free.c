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
struct etnaviv_gpu {int /*<<< orphan*/  event_free; int /*<<< orphan*/  event_spinlock; int /*<<< orphan*/  event_bitmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void event_free(struct etnaviv_gpu *gpu, unsigned int event)
{
	unsigned long flags;

	spin_lock_irqsave(&gpu->event_spinlock, flags);

	if (!test_bit(event, gpu->event_bitmap)) {
		dev_warn(gpu->dev, "event %u is already marked as free",
			 event);
		spin_unlock_irqrestore(&gpu->event_spinlock, flags);
	} else {
		clear_bit(event, gpu->event_bitmap);
		spin_unlock_irqrestore(&gpu->event_spinlock, flags);

		complete(&gpu->event_free);
	}
}