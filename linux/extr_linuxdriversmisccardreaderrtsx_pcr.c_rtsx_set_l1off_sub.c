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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  L1SUB_CONFIG3 ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int rtsx_set_l1off_sub(struct rtsx_pcr *pcr, u8 val)
{
	rtsx_pci_write_register(pcr, L1SUB_CONFIG3, 0xFF, val);

	return 0;
}