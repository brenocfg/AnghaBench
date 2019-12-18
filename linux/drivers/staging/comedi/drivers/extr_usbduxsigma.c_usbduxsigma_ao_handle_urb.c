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
typedef  int /*<<< orphan*/  u8 ;
struct usbduxsigma_private {scalar_t__ ao_counter; scalar_t__ ao_timer; } ;
struct urb {int interval; int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ status; int /*<<< orphan*/  dev; void* transfer_buffer_length; int /*<<< orphan*/ * transfer_buffer; } ;
struct comedi_subdevice {unsigned short* readback; struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct usbduxsigma_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {scalar_t__ scans_done; int events; struct comedi_cmd cmd; } ;
struct TYPE_2__ {scalar_t__ status; void* length; scalar_t__ offset; } ;

/* Variables and functions */
 int COMEDI_CB_CANCEL_MASK ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int COMEDI_CB_OVERFLOW ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EL2NSYNC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* SIZEOUTBUF ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_read_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbduxsigma_ao_handle_urb(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct urb *urb)
{
	struct usbduxsigma_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	u8 *datap;
	int ret;
	int i;

	devpriv->ao_counter--;
	if (devpriv->ao_counter == 0) {
		devpriv->ao_counter = devpriv->ao_timer;

		if (cmd->stop_src == TRIG_COUNT &&
		    async->scans_done >= cmd->stop_arg) {
			async->events |= COMEDI_CB_EOA;
			return;
		}

		/* transmit data to the USB bus */
		datap = urb->transfer_buffer;
		*datap++ = cmd->chanlist_len;
		for (i = 0; i < cmd->chanlist_len; i++) {
			unsigned int chan = CR_CHAN(cmd->chanlist[i]);
			unsigned short val;

			if (!comedi_buf_read_samples(s, &val, 1)) {
				dev_err(dev->class_dev, "buffer underflow\n");
				async->events |= COMEDI_CB_OVERFLOW;
				return;
			}

			*datap++ = val;
			*datap++ = chan;
			s->readback[chan] = val;
		}
	}

	/* if command is still running, resubmit urb */
	if (!(async->events & COMEDI_CB_CANCEL_MASK)) {
		urb->transfer_buffer_length = SIZEOUTBUF;
		urb->dev = comedi_to_usb_dev(dev);
		urb->status = 0;
		urb->interval = 1;	/* (u)frames */
		urb->number_of_packets = 1;
		urb->iso_frame_desc[0].offset = 0;
		urb->iso_frame_desc[0].length = SIZEOUTBUF;
		urb->iso_frame_desc[0].status = 0;
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		if (ret < 0) {
			dev_err(dev->class_dev, "urb resubmit failed (%d)\n",
				ret);
			if (ret == -EL2NSYNC)
				dev_err(dev->class_dev,
					"buggy USB host controller or bug in IRQ handler\n");
			async->events |= COMEDI_CB_ERROR;
		}
	}
}