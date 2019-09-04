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
struct lis3lv02d {int /*<<< orphan*/  wake_thread; int /*<<< orphan*/  async_queue; int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  count; int /*<<< orphan*/  misc_opened; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lis302dl_interrupt(int irq, void *data)
{
	struct lis3lv02d *lis3 = data;

	if (!test_bit(0, &lis3->misc_opened))
		goto out;

	/*
	 * Be careful: on some HP laptops the bios force DD when on battery and
	 * the lid is closed. This leads to interrupts as soon as a little move
	 * is done.
	 */
	atomic_inc(&lis3->count);

	wake_up_interruptible(&lis3->misc_wait);
	kill_fasync(&lis3->async_queue, SIGIO, POLL_IN);
out:
	if (atomic_read(&lis3->wake_thread))
		return IRQ_WAKE_THREAD;
	return IRQ_HANDLED;
}