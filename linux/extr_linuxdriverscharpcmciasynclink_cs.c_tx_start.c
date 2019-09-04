#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_7__ {int flags; scalar_t__ mode; } ;
struct TYPE_8__ {int drop_rts_on_tx_done; int serial_signals; int tx_active; int tx_enabled; int /*<<< orphan*/  tx_timer; TYPE_1__ params; scalar_t__ tx_count; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_ISR ; 
 int HDLC_FLAG_AUTO_RTS ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int SerialSignal_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  get_signals (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_signals (TYPE_2__*) ; 
 int /*<<< orphan*/  tx_ready (TYPE_2__*,struct tty_struct*) ; 

__attribute__((used)) static void tx_start(MGSLPC_INFO *info, struct tty_struct *tty)
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):tx_start(%s)\n",
			 __FILE__, __LINE__, info->device_name);

	if (info->tx_count) {
		/* If auto RTS enabled and RTS is inactive, then assert */
		/* RTS and set a flag indicating that the driver should */
		/* negate RTS when the transmission completes. */
		info->drop_rts_on_tx_done = false;

		if (info->params.flags & HDLC_FLAG_AUTO_RTS) {
			get_signals(info);
			if (!(info->serial_signals & SerialSignal_RTS)) {
				info->serial_signals |= SerialSignal_RTS;
				set_signals(info);
				info->drop_rts_on_tx_done = true;
			}
		}

		if (info->params.mode == MGSL_MODE_ASYNC) {
			if (!info->tx_active) {
				info->tx_active = true;
				tx_ready(info, tty);
			}
		} else {
			info->tx_active = true;
			tx_ready(info, tty);
			mod_timer(&info->tx_timer, jiffies +
					msecs_to_jiffies(5000));
		}
	}

	if (!info->tx_enabled)
		info->tx_enabled = true;
}