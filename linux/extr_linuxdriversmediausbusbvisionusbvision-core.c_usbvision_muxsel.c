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
struct usb_usbvision {int ctl_input; size_t dev_model; int /*<<< orphan*/  video_inputs; } ;
struct TYPE_2__ {int codec; } ;

/* Variables and functions */
#define  CODEC_SAA7111 129 
#define  CODEC_SAA7113 128 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SAA7115_COMPOSITE0 ; 
 int SAA7115_COMPOSITE1 ; 
 int SAA7115_COMPOSITE2 ; 
 int SAA7115_COMPOSITE3 ; 
 int SAA7115_SVIDEO1 ; 
 int /*<<< orphan*/  call_all (struct usb_usbvision*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  switch_svideo_input ; 
 TYPE_1__* usbvision_device_data ; 
 int /*<<< orphan*/  usbvision_set_audio (struct usb_usbvision*,int) ; 
 int /*<<< orphan*/  video ; 

int usbvision_muxsel(struct usb_usbvision *usbvision, int channel)
{
	/* inputs #0 and #3 are constant for every SAA711x. */
	/* inputs #1 and #2 are variable for SAA7111 and SAA7113 */
	int mode[4] = { SAA7115_COMPOSITE0, 0, 0, SAA7115_COMPOSITE3 };
	int audio[] = { 1, 0, 0, 0 };
	/* channel 0 is TV with audiochannel 1 (tuner mono) */
	/* channel 1 is Composite with audio channel 0 (line in) */
	/* channel 2 is S-Video with audio channel 0 (line in) */
	/* channel 3 is additional video inputs to the device with audio channel 0 (line in) */

	RESTRICT_TO_RANGE(channel, 0, usbvision->video_inputs);
	usbvision->ctl_input = channel;

	/* set the new channel */
	/* Regular USB TV Tuners -> channel: 0 = Television, 1 = Composite, 2 = S-Video */
	/* Four video input devices -> channel: 0 = Chan White, 1 = Chan Green, 2 = Chan Yellow, 3 = Chan Red */

	switch (usbvision_device_data[usbvision->dev_model].codec) {
	case CODEC_SAA7113:
		mode[1] = SAA7115_COMPOSITE2;
		if (switch_svideo_input) {
			/* To handle problems with S-Video Input for
			 * some devices.  Use switch_svideo_input
			 * parameter when loading the module.*/
			mode[2] = SAA7115_COMPOSITE1;
		} else {
			mode[2] = SAA7115_SVIDEO1;
		}
		break;
	case CODEC_SAA7111:
	default:
		/* modes for saa7111 */
		mode[1] = SAA7115_COMPOSITE1;
		mode[2] = SAA7115_SVIDEO1;
		break;
	}
	call_all(usbvision, video, s_routing, mode[channel], 0, 0);
	usbvision_set_audio(usbvision, audio[channel]);
	return 0;
}