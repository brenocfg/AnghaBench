#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {scalar_t__ status; scalar_t__ actual_length; scalar_t__ context; } ;
struct smsusb_urb_t {int /*<<< orphan*/  wq; TYPE_1__* cb; struct smsusb_device_t* dev; } ;
struct smsusb_device_t {scalar_t__ response_alignment; int /*<<< orphan*/  coredev; } ;
struct sms_msg_hdr {scalar_t__ msg_length; int msg_flags; int /*<<< orphan*/  msg_type; } ;
struct sms_msg_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ offset; scalar_t__ p; } ;

/* Variables and functions */
 scalar_t__ ESHUTDOWN ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MSG_HDR_FLAG_SPLIT_MSG ; 
 int /*<<< orphan*/  do_submit_urb ; 
 int /*<<< orphan*/  memcpy (char*,struct sms_msg_hdr*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smscore_onresponse (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  smscore_translate_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsendian_handle_message_header (struct sms_msg_hdr*) ; 
 int /*<<< orphan*/  smsendian_handle_rx_message (struct sms_msg_data*) ; 

__attribute__((used)) static void smsusb_onresponse(struct urb *urb)
{
	struct smsusb_urb_t *surb = (struct smsusb_urb_t *) urb->context;
	struct smsusb_device_t *dev = surb->dev;

	if (urb->status == -ESHUTDOWN) {
		pr_err("error, urb status %d (-ESHUTDOWN), %d bytes\n",
			urb->status, urb->actual_length);
		return;
	}

	if ((urb->actual_length > 0) && (urb->status == 0)) {
		struct sms_msg_hdr *phdr = (struct sms_msg_hdr *)surb->cb->p;

		smsendian_handle_message_header(phdr);
		if (urb->actual_length >= phdr->msg_length) {
			surb->cb->size = phdr->msg_length;

			if (dev->response_alignment &&
			    (phdr->msg_flags & MSG_HDR_FLAG_SPLIT_MSG)) {

				surb->cb->offset =
					dev->response_alignment +
					((phdr->msg_flags >> 8) & 3);

				/* sanity check */
				if (((int) phdr->msg_length +
				     surb->cb->offset) > urb->actual_length) {
					pr_err("invalid response msglen %d offset %d size %d\n",
						phdr->msg_length,
						surb->cb->offset,
						urb->actual_length);
					goto exit_and_resubmit;
				}

				/* move buffer pointer and
				 * copy header to its new location */
				memcpy((char *) phdr + surb->cb->offset,
				       phdr, sizeof(struct sms_msg_hdr));
			} else
				surb->cb->offset = 0;

			pr_debug("received %s(%d) size: %d\n",
				  smscore_translate_msg(phdr->msg_type),
				  phdr->msg_type, phdr->msg_length);

			smsendian_handle_rx_message((struct sms_msg_data *) phdr);

			smscore_onresponse(dev->coredev, surb->cb);
			surb->cb = NULL;
		} else {
			pr_err("invalid response msglen %d actual %d\n",
				phdr->msg_length, urb->actual_length);
		}
	} else
		pr_err("error, urb status %d, %d bytes\n",
			urb->status, urb->actual_length);


exit_and_resubmit:
	INIT_WORK(&surb->wq, do_submit_urb);
	schedule_work(&surb->wq);
}