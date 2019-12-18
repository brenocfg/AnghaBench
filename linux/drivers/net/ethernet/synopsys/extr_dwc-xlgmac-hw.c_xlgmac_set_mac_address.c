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
struct xlgmac_pdata {scalar_t__ mac_regs; } ;

/* Variables and functions */
 scalar_t__ MAC_MACA0HR ; 
 scalar_t__ MAC_MACA0LR ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int xlgmac_set_mac_address(struct xlgmac_pdata *pdata, u8 *addr)
{
	unsigned int mac_addr_hi, mac_addr_lo;

	mac_addr_hi = (addr[5] <<  8) | (addr[4] <<  0);
	mac_addr_lo = (addr[3] << 24) | (addr[2] << 16) |
		      (addr[1] <<  8) | (addr[0] <<  0);

	writel(mac_addr_hi, pdata->mac_regs + MAC_MACA0HR);
	writel(mac_addr_lo, pdata->mac_regs + MAC_MACA0LR);

	return 0;
}