#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_4__ {scalar_t__ mode; } ;
struct TYPE_5__ {unsigned char* tx_buf; int tx_count; int tx_put; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_active; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int TXBUFSIZE ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mgslpc_put_char(struct tty_struct *tty, unsigned char ch)
{
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO) {
		printk("%s(%d):mgslpc_put_char(%d) on %s\n",
			__FILE__, __LINE__, ch, info->device_name);
	}

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_put_char"))
		return 0;

	if (!info->tx_buf)
		return 0;

	spin_lock_irqsave(&info->lock, flags);

	if (info->params.mode == MGSL_MODE_ASYNC || !info->tx_active) {
		if (info->tx_count < TXBUFSIZE - 1) {
			info->tx_buf[info->tx_put++] = ch;
			info->tx_put &= TXBUFSIZE-1;
			info->tx_count++;
		}
	}

	spin_unlock_irqrestore(&info->lock, flags);
	return 1;
}