#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  hw_stopped; int /*<<< orphan*/  stopped; int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_5__ {scalar_t__ mode; } ;
struct TYPE_6__ {int tx_count; int tx_put; int /*<<< orphan*/  device_name; int /*<<< orphan*/  lock; scalar_t__ tx_active; scalar_t__ tx_buf; TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EIO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 int TXBUFSIZE ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_start (TYPE_2__*,struct tty_struct*) ; 

__attribute__((used)) static int mgslpc_write(struct tty_struct * tty,
			const unsigned char *buf, int count)
{
	int c, ret = 0;
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_write(%s) count=%d\n",
			__FILE__, __LINE__, info->device_name, count);

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_write") ||
		!info->tx_buf)
		goto cleanup;

	if (info->params.mode == MGSL_MODE_HDLC) {
		if (count > TXBUFSIZE) {
			ret = -EIO;
			goto cleanup;
		}
		if (info->tx_active)
			goto cleanup;
		else if (info->tx_count)
			goto start;
	}

	for (;;) {
		c = min(count,
			min(TXBUFSIZE - info->tx_count - 1,
			    TXBUFSIZE - info->tx_put));
		if (c <= 0)
			break;

		memcpy(info->tx_buf + info->tx_put, buf, c);

		spin_lock_irqsave(&info->lock, flags);
		info->tx_put = (info->tx_put + c) & (TXBUFSIZE-1);
		info->tx_count += c;
		spin_unlock_irqrestore(&info->lock, flags);

		buf += c;
		count -= c;
		ret += c;
	}
start:
	if (info->tx_count && !tty->stopped && !tty->hw_stopped) {
		spin_lock_irqsave(&info->lock, flags);
		if (!info->tx_active)
			tx_start(info, tty);
		spin_unlock_irqrestore(&info->lock, flags);
	}
cleanup:
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_write(%s) returning=%d\n",
			__FILE__, __LINE__, info->device_name, ret);
	return ret;
}