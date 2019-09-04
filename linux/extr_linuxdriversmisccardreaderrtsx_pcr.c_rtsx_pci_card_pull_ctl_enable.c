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
typedef  int /*<<< orphan*/  u32 ;
struct rtsx_pcr {int /*<<< orphan*/ * ms_pull_ctl_enable_tbl; int /*<<< orphan*/ * sd_pull_ctl_enable_tbl; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTSX_MS_CARD ; 
 int RTSX_SD_CARD ; 
 int rtsx_pci_set_pull_ctl (struct rtsx_pcr*,int /*<<< orphan*/  const*) ; 

int rtsx_pci_card_pull_ctl_enable(struct rtsx_pcr *pcr, int card)
{
	const u32 *tbl;

	if (card == RTSX_SD_CARD)
		tbl = pcr->sd_pull_ctl_enable_tbl;
	else if (card == RTSX_MS_CARD)
		tbl = pcr->ms_pull_ctl_enable_tbl;
	else
		return -EINVAL;

	return rtsx_pci_set_pull_ctl(pcr, tbl);
}