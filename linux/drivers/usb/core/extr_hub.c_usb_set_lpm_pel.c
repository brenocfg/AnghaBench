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
struct usb_hub {int dummy; } ;
struct usb_device {int dummy; } ;
struct usb3_lpm_parameters {unsigned int pel; } ;

/* Variables and functions */

__attribute__((used)) static void usb_set_lpm_pel(struct usb_device *udev,
		struct usb3_lpm_parameters *udev_lpm_params,
		unsigned int udev_exit_latency,
		struct usb_hub *hub,
		struct usb3_lpm_parameters *hub_lpm_params,
		unsigned int hub_exit_latency,
		unsigned int port_to_port_exit_latency)
{
	unsigned int first_link_pel;
	unsigned int hub_pel;

	/*
	 * First, the device sends an LFPS to transition the link between the
	 * device and the parent hub into U0.  The exit latency is the bigger of
	 * the device exit latency or the hub exit latency.
	 */
	if (udev_exit_latency > hub_exit_latency)
		first_link_pel = udev_exit_latency * 1000;
	else
		first_link_pel = hub_exit_latency * 1000;

	/*
	 * When the hub starts to receive the LFPS, there is a slight delay for
	 * it to figure out that one of the ports is sending an LFPS.  Then it
	 * will forward the LFPS to its upstream link.  The exit latency is the
	 * delay, plus the PEL that we calculated for this hub.
	 */
	hub_pel = port_to_port_exit_latency * 1000 + hub_lpm_params->pel;

	/*
	 * According to figure C-7 in the USB 3.0 spec, the PEL for this device
	 * is the greater of the two exit latencies.
	 */
	if (first_link_pel > hub_pel)
		udev_lpm_params->pel = first_link_pel;
	else
		udev_lpm_params->pel = hub_pel;
}