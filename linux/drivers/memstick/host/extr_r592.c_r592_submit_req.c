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
struct r592_device {int /*<<< orphan*/  io_thread_lock; int /*<<< orphan*/  io_thread; scalar_t__ req; } ;
struct memstick_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 struct r592_device* memstick_priv (struct memstick_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r592_submit_req(struct memstick_host *host)
{
	struct r592_device *dev = memstick_priv(host);
	unsigned long flags;

	if (dev->req)
		return;

	spin_lock_irqsave(&dev->io_thread_lock, flags);
	if (wake_up_process(dev->io_thread))
		dbg_verbose("IO thread woken to process requests");
	spin_unlock_irqrestore(&dev->io_thread_lock, flags);
}