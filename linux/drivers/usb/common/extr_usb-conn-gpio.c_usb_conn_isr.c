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
struct usb_conn_info {int /*<<< orphan*/  debounce_jiffies; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  usb_conn_queue_dwork (struct usb_conn_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t usb_conn_isr(int irq, void *dev_id)
{
	struct usb_conn_info *info = dev_id;

	usb_conn_queue_dwork(info, info->debounce_jiffies);

	return IRQ_HANDLED;
}