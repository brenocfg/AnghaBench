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
struct pcan_usb_pro_rxts {int /*<<< orphan*/ * ts64; } ;
struct pcan_usb_pro_interface {scalar_t__ cm_ignore_count; int /*<<< orphan*/  time_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peak_usb_set_ts_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcan_usb_pro_handle_ts(struct pcan_usb_pro_interface *usb_if,
				   struct pcan_usb_pro_rxts *ts)
{
	/* should wait until clock is stabilized */
	if (usb_if->cm_ignore_count > 0)
		usb_if->cm_ignore_count--;
	else
		peak_usb_set_ts_now(&usb_if->time_ref,
				    le32_to_cpu(ts->ts64[1]));
}