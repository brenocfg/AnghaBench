#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rx_enabled; int rx_overflow; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BIT3 ; 
 scalar_t__ CHA ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ MODE ; 
 int /*<<< orphan*/  clear_reg_bits (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_stop(MGSLPC_INFO *info)
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):rx_stop(%s)\n",
			 __FILE__, __LINE__, info->device_name);

	/* MODE:03 RAC Receiver Active, 0=inactive */
	clear_reg_bits(info, CHA + MODE, BIT3);

	info->rx_enabled = false;
	info->rx_overflow = false;
}