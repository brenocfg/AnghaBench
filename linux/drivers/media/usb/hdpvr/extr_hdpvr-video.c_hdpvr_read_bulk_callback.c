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
struct urb {scalar_t__ context; } ;
struct hdpvr_device {int /*<<< orphan*/  wait_data; } ;
struct hdpvr_buffer {int /*<<< orphan*/  status; struct hdpvr_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSTAT_READY ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdpvr_read_bulk_callback(struct urb *urb)
{
	struct hdpvr_buffer *buf = (struct hdpvr_buffer *)urb->context;
	struct hdpvr_device *dev = buf->dev;

	/* marking buffer as received and wake waiting */
	buf->status = BUFSTAT_READY;
	wake_up_interruptible(&dev->wait_data);
}