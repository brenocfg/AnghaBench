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
struct net_device {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ARPHRD_IEEE802 ; 
 scalar_t__ ARPHRD_LOOPBACK ; 
 scalar_t__ loopback_enabled ; 

__attribute__((used)) static int siw_dev_qualified(struct net_device *netdev)
{
	/*
	 * Additional hardware support can be added here
	 * (e.g. ARPHRD_FDDI, ARPHRD_ATM, ...) - see
	 * <linux/if_arp.h> for type identifiers.
	 */
	if (netdev->type == ARPHRD_ETHER || netdev->type == ARPHRD_IEEE802 ||
	    (netdev->type == ARPHRD_LOOPBACK && loopback_enabled))
		return 1;

	return 0;
}