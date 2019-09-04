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
typedef  int u32 ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_MAC_ADDR_HIGH ; 
 int /*<<< orphan*/  MVNETA_MAC_ADDR_LOW ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_get_mac_addr(struct mvneta_port *pp, unsigned char *addr)
{
	u32 mac_addr_l, mac_addr_h;

	mac_addr_l = mvreg_read(pp, MVNETA_MAC_ADDR_LOW);
	mac_addr_h = mvreg_read(pp, MVNETA_MAC_ADDR_HIGH);
	addr[0] = (mac_addr_h >> 24) & 0xFF;
	addr[1] = (mac_addr_h >> 16) & 0xFF;
	addr[2] = (mac_addr_h >> 8) & 0xFF;
	addr[3] = mac_addr_h & 0xFF;
	addr[4] = (mac_addr_l >> 8) & 0xFF;
	addr[5] = mac_addr_l & 0xFF;
}