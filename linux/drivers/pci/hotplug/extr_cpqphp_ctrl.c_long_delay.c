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

/* Variables and functions */
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void long_delay(int delay)
{
	/*
	 * XXX(hch): if someone is bored please convert all callers
	 * to call msleep_interruptible directly.  They really want
	 * to specify timeouts in natural units and spend a lot of
	 * effort converting them to jiffies..
	 */
	msleep_interruptible(jiffies_to_msecs(delay));
}