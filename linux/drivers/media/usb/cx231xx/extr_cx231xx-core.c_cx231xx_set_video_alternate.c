#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_8__ {int alt; int* alt_max_pkt_size; int max_pkt_size; } ;
struct TYPE_7__ {TYPE_2__* hs_config_info; } ;
struct cx231xx {int width; int height; scalar_t__ USE_ISO; TYPE_4__ video_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  udev; TYPE_3__ current_pcb_config; } ;
struct TYPE_5__ {scalar_t__ video_index; } ;
struct TYPE_6__ {TYPE_1__ interface_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx231xx_coredbg (char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int usb_set_interface (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

int cx231xx_set_video_alternate(struct cx231xx *dev)
{
	int errCode, prev_alt = dev->video_mode.alt;
	unsigned int min_pkt_size = dev->width * 2 + 4;
	u32 usb_interface_index = 0;

	/* When image size is bigger than a certain value,
	   the frame size should be increased, otherwise, only
	   green screen will be received.
	 */
	if (dev->width * 2 * dev->height > 720 * 240 * 2)
		min_pkt_size *= 2;

	if (dev->width > 360) {
		/* resolutions: 720,704,640 */
		dev->video_mode.alt = 3;
	} else if (dev->width > 180) {
		/* resolutions: 360,352,320,240 */
		dev->video_mode.alt = 2;
	} else if (dev->width > 0) {
		/* resolutions: 180,176,160,128,88 */
		dev->video_mode.alt = 1;
	} else {
		/* Change to alt0 BULK to release USB bandwidth */
		dev->video_mode.alt = 0;
	}

	if (dev->USE_ISO == 0)
		dev->video_mode.alt = 0;

	cx231xx_coredbg("dev->video_mode.alt= %d\n", dev->video_mode.alt);

	/* Get the correct video interface Index */
	usb_interface_index =
	    dev->current_pcb_config.hs_config_info[0].interface_info.
	    video_index + 1;

	if (dev->video_mode.alt != prev_alt) {
		cx231xx_coredbg("minimum isoc packet size: %u (alt=%d)\n",
				min_pkt_size, dev->video_mode.alt);

		if (dev->video_mode.alt_max_pkt_size != NULL)
			dev->video_mode.max_pkt_size =
			dev->video_mode.alt_max_pkt_size[dev->video_mode.alt];
		cx231xx_coredbg("setting alternate %d with wMaxPacketSize=%u\n",
				dev->video_mode.alt,
				dev->video_mode.max_pkt_size);
		errCode =
		    usb_set_interface(dev->udev, usb_interface_index,
				      dev->video_mode.alt);
		if (errCode < 0) {
			dev_err(dev->dev,
				"cannot change alt number to %d (error=%i)\n",
				dev->video_mode.alt, errCode);
			return errCode;
		}
	}
	return 0;
}