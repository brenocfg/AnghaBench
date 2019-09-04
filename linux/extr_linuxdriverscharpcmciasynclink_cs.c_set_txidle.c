#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int idle_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_set_idle (TYPE_1__*) ; 

__attribute__((used)) static int set_txidle(MGSLPC_INFO * info, int idle_mode)
{
	unsigned long flags;
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("set_txidle(%s,%d)\n", info->device_name, idle_mode);
	spin_lock_irqsave(&info->lock, flags);
	info->idle_mode = idle_mode;
	tx_set_idle(info);
	spin_unlock_irqrestore(&info->lock, flags);
	return 0;
}