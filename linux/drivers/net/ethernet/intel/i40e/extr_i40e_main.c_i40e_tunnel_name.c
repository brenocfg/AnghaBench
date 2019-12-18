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
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 

__attribute__((used)) static const char *i40e_tunnel_name(u8 type)
{
	switch (type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		return "vxlan";
	case UDP_TUNNEL_TYPE_GENEVE:
		return "geneve";
	default:
		return "unknown";
	}
}