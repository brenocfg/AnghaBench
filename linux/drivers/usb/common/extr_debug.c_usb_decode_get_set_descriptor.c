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
typedef  scalar_t__ __u8 ;
typedef  int __u16 ;

/* Variables and functions */
#define  USB_DT_BOS 143 
#define  USB_DT_CONFIG 142 
#define  USB_DT_DEBUG 141 
#define  USB_DT_DEVICE 140 
#define  USB_DT_DEVICE_CAPABILITY 139 
#define  USB_DT_DEVICE_QUALIFIER 138 
#define  USB_DT_ENDPOINT 137 
#define  USB_DT_INTERFACE 136 
#define  USB_DT_INTERFACE_ASSOCIATION 135 
#define  USB_DT_INTERFACE_POWER 134 
#define  USB_DT_OTG 133 
#define  USB_DT_OTHER_SPEED_CONFIG 132 
#define  USB_DT_PIPE_USAGE 131 
#define  USB_DT_SSP_ISOC_ENDPOINT_COMP 130 
#define  USB_DT_SS_ENDPOINT_COMP 129 
#define  USB_DT_STRING 128 
 scalar_t__ USB_REQ_GET_DESCRIPTOR ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,int,int) ; 

__attribute__((used)) static void usb_decode_get_set_descriptor(__u8 bRequestType, __u8 bRequest,
					  __u16 wValue, __u16 wIndex,
					  __u16 wLength, char *str, size_t size)
{
	char *s;

	switch (wValue >> 8) {
	case USB_DT_DEVICE:
		s = "Device";
		break;
	case USB_DT_CONFIG:
		s = "Configuration";
		break;
	case USB_DT_STRING:
		s = "String";
		break;
	case USB_DT_INTERFACE:
		s = "Interface";
		break;
	case USB_DT_ENDPOINT:
		s = "Endpoint";
		break;
	case USB_DT_DEVICE_QUALIFIER:
		s = "Device Qualifier";
		break;
	case USB_DT_OTHER_SPEED_CONFIG:
		s = "Other Speed Config";
		break;
	case USB_DT_INTERFACE_POWER:
		s = "Interface Power";
		break;
	case USB_DT_OTG:
		s = "OTG";
		break;
	case USB_DT_DEBUG:
		s = "Debug";
		break;
	case USB_DT_INTERFACE_ASSOCIATION:
		s = "Interface Association";
		break;
	case USB_DT_BOS:
		s = "BOS";
		break;
	case USB_DT_DEVICE_CAPABILITY:
		s = "Device Capability";
		break;
	case USB_DT_PIPE_USAGE:
		s = "Pipe Usage";
		break;
	case USB_DT_SS_ENDPOINT_COMP:
		s = "SS Endpoint Companion";
		break;
	case USB_DT_SSP_ISOC_ENDPOINT_COMP:
		s = "SSP Isochronous Endpoint Companion";
		break;
	default:
		s = "UNKNOWN";
		break;
	}

	snprintf(str, size, "%s %s Descriptor(Index = %d, Length = %d)",
		bRequest == USB_REQ_GET_DESCRIPTOR ? "Get" : "Set",
		s, wValue & 0xff, wLength);
}