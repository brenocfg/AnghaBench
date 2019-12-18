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
struct usbip_device {scalar_t__ event; int /*<<< orphan*/  eh_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

int usbip_start_eh(struct usbip_device *ud)
{
	init_waitqueue_head(&ud->eh_waitq);
	ud->event = 0;
	return 0;
}