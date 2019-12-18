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
typedef  int u64 ;
struct usbnet {int /*<<< orphan*/  net; struct aqc111_data* driver_priv; } ;
struct urb {int actual_length; int* transfer_buffer; } ;
struct aqc111_data {int link_speed; int link; } ;

/* Variables and functions */
 int AQ_LS_MASK ; 
 int AQ_SPEED_MASK ; 
 int AQ_SPEED_SHIFT ; 
 int /*<<< orphan*/  EVENT_LINK_RESET ; 
 int /*<<< orphan*/  le64_to_cpus (int*) ; 
 int netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbnet_defer_kevent (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aqc111_status(struct usbnet *dev, struct urb *urb)
{
	struct aqc111_data *aqc111_data = dev->driver_priv;
	u64 *event_data = NULL;
	int link = 0;

	if (urb->actual_length < sizeof(*event_data))
		return;

	event_data = urb->transfer_buffer;
	le64_to_cpus(event_data);

	if (*event_data & AQ_LS_MASK)
		link = 1;
	else
		link = 0;

	aqc111_data->link_speed = (*event_data & AQ_SPEED_MASK) >>
				  AQ_SPEED_SHIFT;
	aqc111_data->link = link;

	if (netif_carrier_ok(dev->net) != link)
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
}