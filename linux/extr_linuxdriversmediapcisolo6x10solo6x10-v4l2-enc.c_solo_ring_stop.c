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
struct solo_dev {int /*<<< orphan*/ * ring_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_IRQ_ENCODER ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solo_irq_off (struct solo_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_ring_stop(struct solo_dev *solo_dev)
{
	if (solo_dev->ring_thread) {
		kthread_stop(solo_dev->ring_thread);
		solo_dev->ring_thread = NULL;
	}

	solo_irq_off(solo_dev, SOLO_IRQ_ENCODER);
}