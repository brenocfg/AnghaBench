#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  txtimeout; } ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct slgt_info {scalar_t__ netcount; int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__ params; scalar_t__ tx_active; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 int /*<<< orphan*/  bh_transmit (struct slgt_info*) ; 
 struct slgt_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlcdev_tx_done (struct slgt_info*) ; 
 struct slgt_info* info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  tx_timer ; 

__attribute__((used)) static void tx_timeout(struct timer_list *t)
{
	struct slgt_info *info = from_timer(info, t, tx_timer);
	unsigned long flags;

	DBGINFO(("%s tx_timeout\n", info->device_name));
	if(info->tx_active && info->params.mode == MGSL_MODE_HDLC) {
		info->icount.txtimeout++;
	}
	spin_lock_irqsave(&info->lock,flags);
	tx_stop(info);
	spin_unlock_irqrestore(&info->lock,flags);

#if SYNCLINK_GENERIC_HDLC
	if (info->netcount)
		hdlcdev_tx_done(info);
	else
#endif
		bh_transmit(info);
}