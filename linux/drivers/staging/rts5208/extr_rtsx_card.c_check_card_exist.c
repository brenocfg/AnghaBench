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
struct rtsx_chip {int card_exist; int* lun2card; } ;

/* Variables and functions */

int check_card_exist(struct rtsx_chip *chip, unsigned int lun)
{
	if (chip->card_exist & chip->lun2card[lun])
		return 1;

	return 0;
}