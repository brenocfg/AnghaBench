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
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int __rtsx_pci_read_phy_register (struct rtsx_pcr*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rts524a_read_phy(struct rtsx_pcr *pcr, u8 addr, u16 *val)
{
	addr = addr & 0x80 ? (addr & 0x7F) | 0x40 : addr;

	return __rtsx_pci_read_phy_register(pcr, addr, val);
}