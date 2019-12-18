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
struct tty_struct {int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct slgt_info {char x_char; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_enabled; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_start (struct slgt_info*) ; 

__attribute__((used)) static void send_xchar(struct tty_struct *tty, char ch)
{
	struct slgt_info *info = tty->driver_data;
	unsigned long flags;

	if (sanity_check(info, tty->name, "send_xchar"))
		return;
	DBGINFO(("%s send_xchar(%d)\n", info->device_name, ch));
	info->x_char = ch;
	if (ch) {
		spin_lock_irqsave(&info->lock,flags);
		if (!info->tx_enabled)
		 	tx_start(info);
		spin_unlock_irqrestore(&info->lock,flags);
	}
}