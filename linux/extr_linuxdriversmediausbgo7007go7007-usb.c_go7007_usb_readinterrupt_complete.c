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
struct urb {int status; scalar_t__ actual_length; scalar_t__ transfer_buffer_length; scalar_t__ transfer_buffer; scalar_t__ context; } ;
struct go7007 {scalar_t__ status; int interrupt_available; int /*<<< orphan*/  interrupt_waitq; void* interrupt_data; void* interrupt_value; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ESHUTDOWN ; 
 scalar_t__ STATUS_SHUTDOWN ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,void*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void go7007_usb_readinterrupt_complete(struct urb *urb)
{
	struct go7007 *go = (struct go7007 *)urb->context;
	__le16 *regs = (__le16 *)urb->transfer_buffer;
	int status = urb->status;

	if (status) {
		if (status != -ESHUTDOWN &&
				go->status != STATUS_SHUTDOWN) {
			dev_err(go->dev, "error in read interrupt: %d\n", urb->status);
		} else {
			wake_up(&go->interrupt_waitq);
			return;
		}
	} else if (urb->actual_length != urb->transfer_buffer_length) {
		dev_err(go->dev, "short read in interrupt pipe!\n");
	} else {
		go->interrupt_available = 1;
		go->interrupt_data = __le16_to_cpu(regs[0]);
		go->interrupt_value = __le16_to_cpu(regs[1]);
		pr_debug("ReadInterrupt: %04x %04x\n",
				go->interrupt_value, go->interrupt_data);
	}

	wake_up(&go->interrupt_waitq);
}