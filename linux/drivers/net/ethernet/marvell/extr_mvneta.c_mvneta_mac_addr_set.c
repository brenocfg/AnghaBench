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
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_MAC_ADDR_HIGH ; 
 int /*<<< orphan*/  MVNETA_MAC_ADDR_LOW ; 
 int /*<<< orphan*/  mvneta_set_ucast_addr (struct mvneta_port*,unsigned char,int) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mvneta_mac_addr_set(struct mvneta_port *pp, unsigned char *addr,
				int queue)
{
	unsigned int mac_h;
	unsigned int mac_l;

	if (queue != -1) {
		mac_l = (addr[4] << 8) | (addr[5]);
		mac_h = (addr[0] << 24) | (addr[1] << 16) |
			(addr[2] << 8) | (addr[3] << 0);

		mvreg_write(pp, MVNETA_MAC_ADDR_LOW, mac_l);
		mvreg_write(pp, MVNETA_MAC_ADDR_HIGH, mac_h);
	}

	/* Accept frames of this address */
	mvneta_set_ucast_addr(pp, addr[5], queue);
}