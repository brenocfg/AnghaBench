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
struct solo_dev {int /*<<< orphan*/ * kthread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_IRQ_VIDEO_IN ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solo_irq_off (struct solo_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_stop_thread(struct solo_dev *solo_dev)
{
	if (!solo_dev->kthread)
		return;

	solo_irq_off(solo_dev, SOLO_IRQ_VIDEO_IN);
	kthread_stop(solo_dev->kthread);
	solo_dev->kthread = NULL;
}