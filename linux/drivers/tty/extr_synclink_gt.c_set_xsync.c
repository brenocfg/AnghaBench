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
struct slgt_info {int xsync; int /*<<< orphan*/  lock; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int /*<<< orphan*/  XSR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wr_reg32 (struct slgt_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_xsync(struct slgt_info *info, int xsync)
{
	unsigned long flags;

	DBGINFO(("%s set_xsync=%x)\n", info->device_name, xsync));
	spin_lock_irqsave(&info->lock, flags);
	info->xsync = xsync;
	wr_reg32(info, XSR, xsync);
	spin_unlock_irqrestore(&info->lock, flags);
	return 0;
}