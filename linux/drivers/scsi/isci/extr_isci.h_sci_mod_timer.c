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
struct sci_timer {int /*<<< orphan*/  timer; scalar_t__ cancel; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 

__attribute__((used)) static inline void sci_mod_timer(struct sci_timer *tmr, unsigned long msec)
{
	tmr->cancel = 0;
	mod_timer(&tmr->timer, jiffies + msecs_to_jiffies(msec));
}