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
struct pucan_msg {int dummy; } ;
struct pcan_usb_fd_if {scalar_t__ cm_ignore_count; int /*<<< orphan*/  time_ref; } ;
struct pcan_ufd_ts_msg {int /*<<< orphan*/  ts_low; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peak_usb_set_ts_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcan_usb_fd_decode_ts(struct pcan_usb_fd_if *usb_if,
				  struct pucan_msg *rx_msg)
{
	struct pcan_ufd_ts_msg *ts = (struct pcan_ufd_ts_msg *)rx_msg;

	/* should wait until clock is stabilized */
	if (usb_if->cm_ignore_count > 0)
		usb_if->cm_ignore_count--;
	else
		peak_usb_set_ts_now(&usb_if->time_ref, le32_to_cpu(ts->ts_low));
}