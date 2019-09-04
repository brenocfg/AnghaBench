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
struct rtsx_pcr {int flags; unsigned int const card_exist; } ;

/* Variables and functions */
 int EIO ; 
#define  MS_EXIST 131 
 int PCR_MS_PMOS ; 
#define  RTSX_MS_CARD 130 
#define  RTSX_SD_CARD 129 
#define  SD_EXIST 128 

int rtsx_pci_card_exclusive_check(struct rtsx_pcr *pcr, int card)
{
	static const unsigned int cd_mask[] = {
		[RTSX_SD_CARD] = SD_EXIST,
		[RTSX_MS_CARD] = MS_EXIST
	};

	if (!(pcr->flags & PCR_MS_PMOS)) {
		/* When using single PMOS, accessing card is not permitted
		 * if the existing card is not the designated one.
		 */
		if (pcr->card_exist & (~cd_mask[card]))
			return -EIO;
	}

	return 0;
}