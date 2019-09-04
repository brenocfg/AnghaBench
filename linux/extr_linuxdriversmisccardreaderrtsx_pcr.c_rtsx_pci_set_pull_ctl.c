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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 

__attribute__((used)) static int rtsx_pci_set_pull_ctl(struct rtsx_pcr *pcr, const u32 *tbl)
{
	rtsx_pci_init_cmd(pcr);

	while (*tbl & 0xFFFF0000) {
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				(u16)(*tbl >> 16), 0xFF, (u8)(*tbl));
		tbl++;
	}

	return rtsx_pci_send_cmd(pcr, 100);
}