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
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct slgt_info {scalar_t__ tx_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tx_load (struct slgt_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void flush_chars(struct tty_struct *tty)
{
	struct slgt_info *info = tty->driver_data;
	unsigned long flags;

	if (sanity_check(info, tty->name, "flush_chars"))
		return;
	DBGINFO(("%s flush_chars entry tx_count=%d\n", info->device_name, info->tx_count));

	if (info->tx_count <= 0 || tty->stopped ||
	    tty->hw_stopped || !info->tx_buf)
		return;

	DBGINFO(("%s flush_chars start transmit\n", info->device_name));

	spin_lock_irqsave(&info->lock,flags);
	if (info->tx_count && tx_load(info, info->tx_buf, info->tx_count))
		info->tx_count = 0;
	spin_unlock_irqrestore(&info->lock,flags);
}