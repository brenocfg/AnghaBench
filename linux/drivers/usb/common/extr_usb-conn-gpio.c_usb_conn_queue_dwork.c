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
struct usb_conn_info {int /*<<< orphan*/  dw_det; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static void usb_conn_queue_dwork(struct usb_conn_info *info,
				 unsigned long delay)
{
	queue_delayed_work(system_power_efficient_wq, &info->dw_det, delay);
}