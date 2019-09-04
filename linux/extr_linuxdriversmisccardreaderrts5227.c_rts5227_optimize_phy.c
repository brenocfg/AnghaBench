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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3_DELINK_MODE_EN ; 
 int /*<<< orphan*/  PM_CTRL3 ; 
 int rtsx_pci_write_phy_register (struct rtsx_pcr*,int,int) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rts5227_optimize_phy(struct rtsx_pcr *pcr)
{
	int err;

	err = rtsx_pci_write_register(pcr, PM_CTRL3, D3_DELINK_MODE_EN, 0x00);
	if (err < 0)
		return err;

	/* Optimize RX sensitivity */
	return rtsx_pci_write_phy_register(pcr, 0x00, 0xBA42);
}