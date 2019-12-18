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
struct amvdec_session {scalar_t__ last_irq_jiffies; } ;

/* Variables and functions */
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_is_after_jiffies64 (scalar_t__) ; 

__attribute__((used)) static void vdec_wait_inactive(struct amvdec_session *sess)
{
	/* We consider 50ms with no IRQ to be inactive. */
	while (time_is_after_jiffies64(sess->last_irq_jiffies +
				       msecs_to_jiffies(50)))
		msleep(25);
}