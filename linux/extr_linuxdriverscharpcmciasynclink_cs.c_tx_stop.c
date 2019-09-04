#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tx_enabled; int tx_active; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_stop(MGSLPC_INFO *info)
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):tx_stop(%s)\n",
			 __FILE__, __LINE__, info->device_name);

	del_timer(&info->tx_timer);

	info->tx_enabled = false;
	info->tx_active = false;
}