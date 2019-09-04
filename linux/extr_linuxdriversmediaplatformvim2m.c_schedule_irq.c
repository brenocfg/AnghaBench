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
struct vim2m_dev {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct vim2m_dev*,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static void schedule_irq(struct vim2m_dev *dev, int msec_timeout)
{
	dprintk(dev, "Scheduling a simulated irq\n");
	mod_timer(&dev->timer, jiffies + msecs_to_jiffies(msec_timeout));
}