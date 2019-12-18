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
struct slgt_info {unsigned char const* tx_buf; int max_frame_size; int tx_count; int /*<<< orphan*/  device_name; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int EIO ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tx_load (struct slgt_info*,unsigned char const*,int) ; 

__attribute__((used)) static int write(struct tty_struct *tty,
		 const unsigned char *buf, int count)
{
	int ret = 0;
	struct slgt_info *info = tty->driver_data;
	unsigned long flags;

	if (sanity_check(info, tty->name, "write"))
		return -EIO;

	DBGINFO(("%s write count=%d\n", info->device_name, count));

	if (!info->tx_buf || (count > info->max_frame_size))
		return -EIO;

	if (!count || tty->stopped || tty->hw_stopped)
		return 0;

	spin_lock_irqsave(&info->lock, flags);

	if (info->tx_count) {
		/* send accumulated data from send_char() */
		if (!tx_load(info, info->tx_buf, info->tx_count))
			goto cleanup;
		info->tx_count = 0;
	}

	if (tx_load(info, buf, count))
		ret = count;

cleanup:
	spin_unlock_irqrestore(&info->lock, flags);
	DBGINFO(("%s write rc=%d\n", info->device_name, ret));
	return ret;
}