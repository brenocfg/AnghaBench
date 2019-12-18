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
struct mv643xx_eth_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_ADDR_HIGH ; 
 int /*<<< orphan*/  MAC_ADDR_LOW ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void uc_addr_set(struct mv643xx_eth_private *mp, unsigned char *addr)
{
	wrlp(mp, MAC_ADDR_HIGH,
		(addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3]);
	wrlp(mp, MAC_ADDR_LOW, (addr[4] << 8) | addr[5]);
}