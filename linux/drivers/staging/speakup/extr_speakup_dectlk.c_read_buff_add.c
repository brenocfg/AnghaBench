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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  flush ; 
 int /*<<< orphan*/  flush_lock ; 
 scalar_t__ is_flushing ; 
 scalar_t__ is_indnum (int*) ; 
 int lastind ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int xoff ; 

__attribute__((used)) static void read_buff_add(u_char c)
{
	static int ind = -1;

	if (c == 0x01) {
		unsigned long flags;

		spin_lock_irqsave(&flush_lock, flags);
		is_flushing = 0;
		wake_up_interruptible(&flush);
		spin_unlock_irqrestore(&flush_lock, flags);
	} else if (c == 0x13) {
		xoff = 1;
	} else if (c == 0x11) {
		xoff = 0;
	} else if (is_indnum(&c)) {
		if (ind == -1)
			ind = c;
		else
			ind = ind * 10 + c;
	} else if ((c > 31) && (c < 127)) {
		if (ind != -1)
			lastind = (u_char)ind;
		ind = -1;
	}
}