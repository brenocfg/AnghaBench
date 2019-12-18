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
typedef  int u32 ;
struct usb_endpoint_descriptor {int dummy; } ;
struct renesas_usb3_ep {int rammap_val; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int PN_RAMMAP_MPKT (int const) ; 
 int const usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static u32 usb3_calc_rammap_val(struct renesas_usb3_ep *usb3_ep,
				const struct usb_endpoint_descriptor *desc)
{
	int i;
	static const u32 max_packet_array[] = {8, 16, 32, 64, 512};
	u32 mpkt = PN_RAMMAP_MPKT(1024);

	for (i = 0; i < ARRAY_SIZE(max_packet_array); i++) {
		if (usb_endpoint_maxp(desc) <= max_packet_array[i])
			mpkt = PN_RAMMAP_MPKT(max_packet_array[i]);
	}

	return usb3_ep->rammap_val | mpkt;
}