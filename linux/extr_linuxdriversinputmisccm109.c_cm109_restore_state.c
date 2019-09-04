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
struct cm109_dev {scalar_t__ open; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_toggle_buzzer_async (struct cm109_dev*) ; 

__attribute__((used)) static void cm109_restore_state(struct cm109_dev *dev)
{
	if (dev->open) {
		/*
		 * Restore buzzer state.
		 * This will also kick regular URB submission
		 */
		cm109_toggle_buzzer_async(dev);
	}
}