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
struct ftgmac100 {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FTGMAC100_OFFSET_MAC_LADR ; 
 scalar_t__ FTGMAC100_OFFSET_MAC_MADR ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 

__attribute__((used)) static void ftgmac100_write_mac_addr(struct ftgmac100 *priv, const u8 *mac)
{
	unsigned int maddr = mac[0] << 8 | mac[1];
	unsigned int laddr = mac[2] << 24 | mac[3] << 16 | mac[4] << 8 | mac[5];

	iowrite32(maddr, priv->base + FTGMAC100_OFFSET_MAC_MADR);
	iowrite32(laddr, priv->base + FTGMAC100_OFFSET_MAC_LADR);
}