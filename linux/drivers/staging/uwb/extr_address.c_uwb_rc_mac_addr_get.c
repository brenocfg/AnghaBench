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
struct uwb_rc {int dummy; } ;
struct uwb_mac_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_ADDR_MAC ; 
 int uwb_rc_addr_get (struct uwb_rc*,struct uwb_mac_addr*,int /*<<< orphan*/ ) ; 

int uwb_rc_mac_addr_get(struct uwb_rc *rc,
			struct uwb_mac_addr *addr) {
	return uwb_rc_addr_get(rc, addr, UWB_ADDR_MAC);
}