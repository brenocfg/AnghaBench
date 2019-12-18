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
struct pasemi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAS_MAC_CFG_PCFG ; 
 unsigned int PAS_MAC_CFG_PCFG_PE ; 
 unsigned int read_mac_reg (struct pasemi_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_mac_reg (struct pasemi_mac*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void pasemi_mac_intf_enable(struct pasemi_mac *mac)
{
	unsigned int flags;

	flags = read_mac_reg(mac, PAS_MAC_CFG_PCFG);
	flags |= PAS_MAC_CFG_PCFG_PE;
	write_mac_reg(mac, PAS_MAC_CFG_PCFG, flags);
}