#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mode; } ;
struct slgt_info {int idle_mode; int /*<<< orphan*/  lock; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_set_idle (struct slgt_info*) ; 

__attribute__((used)) static int set_txidle(struct slgt_info *info, int idle_mode)
{
 	unsigned long flags;
	DBGINFO(("%s set_txidle(%d)\n", info->device_name, idle_mode));
	spin_lock_irqsave(&info->lock,flags);
	info->idle_mode = idle_mode;
	if (info->params.mode != MGSL_MODE_ASYNC)
		tx_set_idle(info);
	spin_unlock_irqrestore(&info->lock,flags);
	return 0;
}