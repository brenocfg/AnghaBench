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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8411B_PACKAGE_MODE ; 
 int /*<<< orphan*/  rtsx_pci_read_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rtl8411b_is_qfn48(struct rtsx_pcr *pcr)
{
	u8 val = 0;

	rtsx_pci_read_register(pcr, RTL8411B_PACKAGE_MODE, &val);

	if (val & 0x2)
		return 1;
	else
		return 0;
}