#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {struct gb_message* context; } ;
struct gb_message {int /*<<< orphan*/ * hcpriv; int /*<<< orphan*/  header; TYPE_2__* operation; } ;
struct gb_host_device {int dummy; } ;
struct es2_ap_dev {int /*<<< orphan*/  cport_out_urb_lock; } ;
struct TYPE_4__ {TYPE_1__* connection; } ;
struct TYPE_3__ {struct gb_host_device* hd; } ;

/* Variables and functions */
 int check_urb_status (struct urb*) ; 
 int /*<<< orphan*/  free_urb (struct es2_ap_dev*,struct urb*) ; 
 int /*<<< orphan*/  gb_message_cport_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  greybus_message_sent (struct gb_host_device*,struct gb_message*,int) ; 
 struct es2_ap_dev* hd_to_es2 (struct gb_host_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cport_out_callback(struct urb *urb)
{
	struct gb_message *message = urb->context;
	struct gb_host_device *hd = message->operation->connection->hd;
	struct es2_ap_dev *es2 = hd_to_es2(hd);
	int status = check_urb_status(urb);
	unsigned long flags;

	gb_message_cport_clear(message->header);

	spin_lock_irqsave(&es2->cport_out_urb_lock, flags);
	message->hcpriv = NULL;
	spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);

	/*
	 * Tell the submitter that the message send (attempt) is
	 * complete, and report the status.
	 */
	greybus_message_sent(hd, message, status);

	free_urb(es2, urb);
}