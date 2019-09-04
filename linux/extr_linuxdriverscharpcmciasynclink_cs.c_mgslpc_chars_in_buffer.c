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
struct TYPE_5__ {int max_frame_size; int tx_count; int /*<<< orphan*/  device_name; scalar_t__ tx_active; TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int mgslpc_chars_in_buffer(struct tty_struct *tty)
{
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	int rc;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_chars_in_buffer(%s)\n",
			 __FILE__, __LINE__, info->device_name);

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_chars_in_buffer"))
		return 0;

	if (info->params.mode == MGSL_MODE_HDLC)
		rc = info->tx_active ? info->max_frame_size : 0;
	else
		rc = info->tx_count;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_chars_in_buffer(%s)=%d\n",
			 __FILE__, __LINE__, info->device_name, rc);

	return rc;
}