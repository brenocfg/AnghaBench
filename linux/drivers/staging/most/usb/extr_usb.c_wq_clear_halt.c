#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct most_dev {int* is_channel_healthy; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  iface; TYPE_2__* usb_device; int /*<<< orphan*/ * ep_address; TYPE_1__* conf; int /*<<< orphan*/ * busy_urbs; } ;
struct clear_hold_work {unsigned int channel; int pipe; struct most_dev* mdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ data_type; scalar_t__ direction; } ;

/* Variables and functions */
 scalar_t__ MOST_CH_ASYNC ; 
 scalar_t__ MOST_CH_RX ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  most_resume_enqueue (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  most_stop_enqueue (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct clear_hold_work* to_clear_hold_work (struct work_struct*) ; 
 scalar_t__ usb_clear_halt (TYPE_2__*,int) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int usb_sndbulkpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wq_clear_halt(struct work_struct *wq_obj)
{
	struct clear_hold_work *clear_work = to_clear_hold_work(wq_obj);
	struct most_dev *mdev = clear_work->mdev;
	unsigned int channel = clear_work->channel;
	int pipe = clear_work->pipe;

	mutex_lock(&mdev->io_mutex);
	most_stop_enqueue(&mdev->iface, channel);
	usb_kill_anchored_urbs(&mdev->busy_urbs[channel]);
	if (usb_clear_halt(mdev->usb_device, pipe))
		dev_warn(&mdev->usb_device->dev, "Failed to reset endpoint.\n");

	/* If the functional Stall condition has been set on an
	 * asynchronous rx channel, we need to clear the tx channel
	 * too, since the hardware runs its clean-up sequence on both
	 * channels, as they are physically one on the network.
	 *
	 * The USB interface that exposes the asynchronous channels
	 * contains always two endpoints, and two only.
	 */
	if (mdev->conf[channel].data_type == MOST_CH_ASYNC &&
	    mdev->conf[channel].direction == MOST_CH_RX) {
		int peer = 1 - channel;
		int snd_pipe = usb_sndbulkpipe(mdev->usb_device,
					       mdev->ep_address[peer]);
		usb_clear_halt(mdev->usb_device, snd_pipe);
	}
	mdev->is_channel_healthy[channel] = true;
	most_resume_enqueue(&mdev->iface, channel);
	mutex_unlock(&mdev->io_mutex);
}