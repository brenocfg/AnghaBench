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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static bool
mac_addr_valid(u8 *mac_addr)
{
	bool is_valid = true;
	ENTER();

	/* Make sure it is not a multicast address */
	if (is_multicast_ether_addr(mac_addr)) {
		pr_debug("MAC address is multicast\n");
		is_valid = false;
	}
	/* Not a broadcast address */
	else if (is_broadcast_ether_addr(mac_addr)) {
		pr_debug("MAC address is broadcast\n");
		is_valid = false;
	}
	/* Reject the zero address */
	else if (is_zero_ether_addr(mac_addr)) {
		pr_debug("MAC address is all zeros\n");
		is_valid = false;
	}
	return is_valid;
}