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
typedef  int u32 ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_update (struct cx18*,int,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_reset_seq(struct cx18 *cx, u32 active_lo, u32 active_hi,
			   unsigned int assert_msecs,
			   unsigned int recovery_msecs)
{
	u32 mask;

	mask = active_lo | active_hi;
	if (mask == 0)
		return;

	/*
	 * Assuming that active_hi and active_lo are a subsets of the bits in
	 * gpio_dir.  Also assumes that active_lo and active_hi don't overlap
	 * in any bit position
	 */

	/* Assert */
	gpio_update(cx, mask, ~active_lo);
	schedule_timeout_uninterruptible(msecs_to_jiffies(assert_msecs));

	/* Deassert */
	gpio_update(cx, mask, ~active_hi);
	schedule_timeout_uninterruptible(msecs_to_jiffies(recovery_msecs));
}