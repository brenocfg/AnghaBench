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
typedef  size_t u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 char** efx_udp_tunnel_type_names ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

void efx_get_udp_tunnel_type_name(u16 type, char *buf, size_t buflen)
{
	if (type < ARRAY_SIZE(efx_udp_tunnel_type_names) &&
	    efx_udp_tunnel_type_names[type] != NULL)
		snprintf(buf, buflen, "%s", efx_udp_tunnel_type_names[type]);
	else
		snprintf(buf, buflen, "type %d", type);
}