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
struct most_dev {TYPE_1__* usb_device; struct most_channel_config* conf; } ;
struct most_channel_config {int dummy; } ;
struct mbo {unsigned int buffer_length; scalar_t__ virt_address; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int USB_MTU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned int get_stream_frame_size (struct most_channel_config*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 

__attribute__((used)) static int hdm_add_padding(struct most_dev *mdev, int channel, struct mbo *mbo)
{
	struct most_channel_config *conf = &mdev->conf[channel];
	unsigned int frame_size = get_stream_frame_size(conf);
	unsigned int j, num_frames;

	if (!frame_size)
		return -EIO;
	num_frames = mbo->buffer_length / frame_size;

	if (num_frames < 1) {
		dev_err(&mdev->usb_device->dev,
			"Missed minimal transfer unit.\n");
		return -EIO;
	}

	for (j = num_frames - 1; j > 0; j--)
		memmove(mbo->virt_address + j * USB_MTU,
			mbo->virt_address + j * frame_size,
			frame_size);
	mbo->buffer_length = num_frames * USB_MTU;
	return 0;
}