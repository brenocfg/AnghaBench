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
struct solo_dev {int /*<<< orphan*/  ring_thread_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void solo_enc_v4l2_isr(struct solo_dev *solo_dev)
{
	wake_up_interruptible_all(&solo_dev->ring_thread_wait);
}