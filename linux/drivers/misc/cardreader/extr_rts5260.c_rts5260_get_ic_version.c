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
 int /*<<< orphan*/  DUMMY_REG_RESET_0 ; 
 int IC_VERSION_MASK ; 
 int /*<<< orphan*/  rtsx_pci_read_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u8 rts5260_get_ic_version(struct rtsx_pcr *pcr)
{
	u8 val;

	rtsx_pci_read_register(pcr, DUMMY_REG_RESET_0, &val);
	return val & IC_VERSION_MASK;
}