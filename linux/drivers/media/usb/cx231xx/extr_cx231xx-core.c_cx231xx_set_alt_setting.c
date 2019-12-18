#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_18__ {scalar_t__ no_alt_vanc; } ;
struct TYPE_17__ {int alt; scalar_t__* alt_max_pkt_size; scalar_t__ max_pkt_size; } ;
struct TYPE_16__ {TYPE_6__* hs_config_info; } ;
struct TYPE_13__ {int alt; scalar_t__* alt_max_pkt_size; scalar_t__ max_pkt_size; } ;
struct TYPE_12__ {int alt; scalar_t__* alt_max_pkt_size; scalar_t__ max_pkt_size; } ;
struct TYPE_11__ {int alt; scalar_t__* alt_max_pkt_size; scalar_t__ max_pkt_size; } ;
struct TYPE_10__ {int alt; scalar_t__* alt_max_pkt_size; scalar_t__ max_pkt_size; } ;
struct cx231xx {int /*<<< orphan*/  dev; int /*<<< orphan*/  udev; TYPE_9__ board; TYPE_8__ sliced_cc_mode; TYPE_7__ current_pcb_config; TYPE_4__ vbi_mode; TYPE_3__ video_mode; TYPE_2__ adev; TYPE_1__ ts1_mode; } ;
struct TYPE_14__ {int /*<<< orphan*/  hanc_index; int /*<<< orphan*/  vanc_index; int /*<<< orphan*/  video_index; int /*<<< orphan*/  audio_index; int /*<<< orphan*/  ts2_index; int /*<<< orphan*/  ts1_index; } ;
struct TYPE_15__ {TYPE_5__ interface_info; } ;

/* Variables and functions */
#define  INDEX_AUDIO 133 
#define  INDEX_HANC 132 
#define  INDEX_TS1 131 
#define  INDEX_TS2 130 
#define  INDEX_VANC 129 
#define  INDEX_VIDEO 128 
 int /*<<< orphan*/  cx231xx_coredbg (char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 int usb_set_interface (int /*<<< orphan*/ ,scalar_t__,int) ; 

int cx231xx_set_alt_setting(struct cx231xx *dev, u8 index, u8 alt)
{
	int status = 0;
	u32 usb_interface_index = 0;
	u32 max_pkt_size = 0;

	switch (index) {
	case INDEX_TS1:
		usb_interface_index =
		    dev->current_pcb_config.hs_config_info[0].interface_info.
		    ts1_index + 1;
		dev->ts1_mode.alt = alt;
		if (dev->ts1_mode.alt_max_pkt_size != NULL)
			max_pkt_size = dev->ts1_mode.max_pkt_size =
			    dev->ts1_mode.alt_max_pkt_size[dev->ts1_mode.alt];
		break;
	case INDEX_TS2:
		usb_interface_index =
		    dev->current_pcb_config.hs_config_info[0].interface_info.
		    ts2_index + 1;
		break;
	case INDEX_AUDIO:
		usb_interface_index =
		    dev->current_pcb_config.hs_config_info[0].interface_info.
		    audio_index + 1;
		dev->adev.alt = alt;
		if (dev->adev.alt_max_pkt_size != NULL)
			max_pkt_size = dev->adev.max_pkt_size =
			    dev->adev.alt_max_pkt_size[dev->adev.alt];
		break;
	case INDEX_VIDEO:
		usb_interface_index =
		    dev->current_pcb_config.hs_config_info[0].interface_info.
		    video_index + 1;
		dev->video_mode.alt = alt;
		if (dev->video_mode.alt_max_pkt_size != NULL)
			max_pkt_size = dev->video_mode.max_pkt_size =
			    dev->video_mode.alt_max_pkt_size[dev->video_mode.
							     alt];
		break;
	case INDEX_VANC:
		if (dev->board.no_alt_vanc)
			return 0;
		usb_interface_index =
		    dev->current_pcb_config.hs_config_info[0].interface_info.
		    vanc_index + 1;
		dev->vbi_mode.alt = alt;
		if (dev->vbi_mode.alt_max_pkt_size != NULL)
			max_pkt_size = dev->vbi_mode.max_pkt_size =
			    dev->vbi_mode.alt_max_pkt_size[dev->vbi_mode.alt];
		break;
	case INDEX_HANC:
		usb_interface_index =
		    dev->current_pcb_config.hs_config_info[0].interface_info.
		    hanc_index + 1;
		dev->sliced_cc_mode.alt = alt;
		if (dev->sliced_cc_mode.alt_max_pkt_size != NULL)
			max_pkt_size = dev->sliced_cc_mode.max_pkt_size =
			    dev->sliced_cc_mode.alt_max_pkt_size[dev->
								 sliced_cc_mode.
								 alt];
		break;
	default:
		break;
	}

	if (alt > 0 && max_pkt_size == 0) {
		dev_err(dev->dev,
			"can't change interface %d alt no. to %d: Max. Pkt size = 0\n",
			usb_interface_index, alt);
		/*To workaround error number=-71 on EP0 for videograbber,
		 need add following codes.*/
		if (dev->board.no_alt_vanc)
			return -1;
	}

	cx231xx_coredbg("setting alternate %d with wMaxPacketSize=%u,Interface = %d\n",
			alt, max_pkt_size,
			usb_interface_index);

	if (usb_interface_index > 0) {
		status = usb_set_interface(dev->udev, usb_interface_index, alt);
		if (status < 0) {
			dev_err(dev->dev,
				"can't change interface %d alt no. to %d (err=%i)\n",
				usb_interface_index, alt, status);
			return status;
		}
	}

	return status;
}