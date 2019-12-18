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
struct usbtest_dev {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct urb {int transfer_buffer_length; int status; int /*<<< orphan*/  pipe; struct usb_device* dev; int /*<<< orphan*/  transfer_flags; struct completion* context; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIMPLE_IO_TIMEOUT ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*,int,int,int) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int simple_check_buf (struct usbtest_dev*,struct urb*) ; 
 int /*<<< orphan*/  simple_fill_buf (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,unsigned long) ; 

__attribute__((used)) static int simple_io(
	struct usbtest_dev	*tdev,
	struct urb		*urb,
	int			iterations,
	int			vary,
	int			expected,
	const char		*label
)
{
	struct usb_device	*udev = urb->dev;
	int			max = urb->transfer_buffer_length;
	struct completion	completion;
	int			retval = 0;
	unsigned long		expire;

	urb->context = &completion;
	while (retval == 0 && iterations-- > 0) {
		init_completion(&completion);
		if (usb_pipeout(urb->pipe)) {
			simple_fill_buf(urb);
			urb->transfer_flags |= URB_ZERO_PACKET;
		}
		retval = usb_submit_urb(urb, GFP_KERNEL);
		if (retval != 0)
			break;

		expire = msecs_to_jiffies(SIMPLE_IO_TIMEOUT);
		if (!wait_for_completion_timeout(&completion, expire)) {
			usb_kill_urb(urb);
			retval = (urb->status == -ENOENT ?
				  -ETIMEDOUT : urb->status);
		} else {
			retval = urb->status;
		}

		urb->dev = udev;
		if (retval == 0 && usb_pipein(urb->pipe))
			retval = simple_check_buf(tdev, urb);

		if (vary) {
			int	len = urb->transfer_buffer_length;

			len += vary;
			len %= max;
			if (len == 0)
				len = (vary < max) ? vary : max;
			urb->transfer_buffer_length = len;
		}

		/* FIXME if endpoint halted, clear halt (and log) */
	}
	urb->transfer_buffer_length = max;

	if (expected != retval)
		dev_err(&udev->dev,
			"%s failed, iterations left %d, status %d (not %d)\n",
				label, iterations, retval, expected);
	return retval;
}