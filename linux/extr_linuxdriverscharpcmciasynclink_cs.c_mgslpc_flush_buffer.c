#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  write_wait; int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_timer; scalar_t__ tx_get; scalar_t__ tx_put; scalar_t__ tx_count; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgslpc_flush_buffer(struct tty_struct *tty)
{
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_flush_buffer(%s) entry\n",
			 __FILE__, __LINE__, info->device_name);

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_flush_buffer"))
		return;

	spin_lock_irqsave(&info->lock, flags);
	info->tx_count = info->tx_put = info->tx_get = 0;
	del_timer(&info->tx_timer);
	spin_unlock_irqrestore(&info->lock, flags);

	wake_up_interruptible(&tty->write_wait);
	tty_wakeup(tty);
}