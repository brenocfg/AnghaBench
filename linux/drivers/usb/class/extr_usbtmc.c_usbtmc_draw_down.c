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
struct usbtmc_file_data {int /*<<< orphan*/  in_anchor; int /*<<< orphan*/  submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 
 int usb_wait_anchor_empty_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void usbtmc_draw_down(struct usbtmc_file_data *file_data)
{
	int time;

	time = usb_wait_anchor_empty_timeout(&file_data->submitted, 1000);
	if (!time)
		usb_kill_anchored_urbs(&file_data->submitted);
	usb_scuttle_anchored_urbs(&file_data->in_anchor);
}