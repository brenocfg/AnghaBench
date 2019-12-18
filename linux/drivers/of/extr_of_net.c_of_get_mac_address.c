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
struct device_node {int dummy; } ;

/* Variables and functions */
 void* of_get_mac_addr (struct device_node*,char*) ; 
 void const* of_get_mac_addr_nvmem (struct device_node*) ; 

const void *of_get_mac_address(struct device_node *np)
{
	const void *addr;

	addr = of_get_mac_addr(np, "mac-address");
	if (addr)
		return addr;

	addr = of_get_mac_addr(np, "local-mac-address");
	if (addr)
		return addr;

	addr = of_get_mac_addr(np, "address");
	if (addr)
		return addr;

	return of_get_mac_addr_nvmem(np);
}