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
typedef  enum usnic_transport_type { ____Placeholder_usnic_transport_type } usnic_transport_type ;

/* Variables and functions */
#define  USNIC_TRANSPORT_IPV4_UDP 131 
#define  USNIC_TRANSPORT_MAX 130 
#define  USNIC_TRANSPORT_ROCE_CUSTOM 129 
#define  USNIC_TRANSPORT_UNKNOWN 128 

const char *usnic_transport_to_str(enum usnic_transport_type type)
{
	switch (type) {
	case USNIC_TRANSPORT_UNKNOWN:
		return "Unknown";
	case USNIC_TRANSPORT_ROCE_CUSTOM:
		return "roce custom";
	case USNIC_TRANSPORT_IPV4_UDP:
		return "IPv4 UDP";
	case USNIC_TRANSPORT_MAX:
		return "Max?";
	default:
		return "Not known";
	}
}