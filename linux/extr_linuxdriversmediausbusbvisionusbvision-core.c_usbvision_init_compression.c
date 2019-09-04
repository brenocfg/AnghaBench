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
struct usb_usbvision {int last_isoc_frame_num; int compr_level; int last_compr_level; int request_intra; scalar_t__ isoc_measure_bandwidth_count; scalar_t__ isoc_urb_count; scalar_t__ isoc_skip_count; scalar_t__ isoc_packet_count; scalar_t__ isoc_data_count; } ;

/* Variables and functions */

__attribute__((used)) static int usbvision_init_compression(struct usb_usbvision *usbvision)
{
	usbvision->last_isoc_frame_num = -1;
	usbvision->isoc_data_count = 0;
	usbvision->isoc_packet_count = 0;
	usbvision->isoc_skip_count = 0;
	usbvision->compr_level = 50;
	usbvision->last_compr_level = -1;
	usbvision->isoc_urb_count = 0;
	usbvision->request_intra = 1;
	usbvision->isoc_measure_bandwidth_count = 0;

	return 0;
}