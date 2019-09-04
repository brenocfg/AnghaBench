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
struct TYPE_5__ {int tx_count; int /*<<< orphan*/  device_name; scalar_t__ tx_active; TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int HDLC_MAX_FRAME_SIZE ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 int TXBUFSIZE ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mgslpc_write_room(struct tty_struct *tty)
{
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	int ret;

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_write_room"))
		return 0;

	if (info->params.mode == MGSL_MODE_HDLC) {
		/* HDLC (frame oriented) mode */
		if (info->tx_active)
			return 0;
		else
			return HDLC_MAX_FRAME_SIZE;
	} else {
		ret = TXBUFSIZE - info->tx_count - 1;
		if (ret < 0)
			ret = 0;
	}

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_write_room(%s)=%d\n",
			 __FILE__, __LINE__, info->device_name, ret);
	return ret;
}