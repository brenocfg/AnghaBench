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
struct usb_device {int dummy; } ;
struct smsusb_device_t {struct usb_device* udev; } ;
struct sms_board {int /*<<< orphan*/  name; } ;
typedef  void media_device ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_cleanup (void*) ; 
 int media_device_register (void*) ; 
 int /*<<< orphan*/  media_device_usb_init (void*,struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct sms_board* sms_get_board (int) ; 

__attribute__((used)) static void *siano_media_device_register(struct smsusb_device_t *dev,
					int board_id)
{
#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	struct media_device *mdev;
	struct usb_device *udev = dev->udev;
	struct sms_board *board = sms_get_board(board_id);
	int ret;

	mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return NULL;

	media_device_usb_init(mdev, udev, board->name);

	ret = media_device_register(mdev);
	if (ret) {
		media_device_cleanup(mdev);
		kfree(mdev);
		return NULL;
	}

	pr_info("media controller created\n");

	return mdev;
#else
	return NULL;
#endif
}