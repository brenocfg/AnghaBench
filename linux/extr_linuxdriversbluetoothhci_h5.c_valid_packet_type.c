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
typedef  int u8 ;

/* Variables and functions */
#define  HCI_3WIRE_ACK_PKT 132 
#define  HCI_3WIRE_LINK_PKT 131 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
#define  HCI_SCODATA_PKT 128 

__attribute__((used)) static bool valid_packet_type(u8 type)
{
	switch (type) {
	case HCI_ACLDATA_PKT:
	case HCI_COMMAND_PKT:
	case HCI_SCODATA_PKT:
	case HCI_3WIRE_LINK_PKT:
	case HCI_3WIRE_ACK_PKT:
		return true;
	default:
		return false;
	}
}