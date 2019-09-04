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
struct urb {int actual_length; scalar_t__ status; struct iforce* context; } ;
struct iforce {int ecmd; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iforce_usb_ctrl(struct urb *urb)
{
	struct iforce *iforce = urb->context;
	if (urb->status) return;
	iforce->ecmd = 0xff00 | urb->actual_length;
	wake_up(&iforce->wait);
}