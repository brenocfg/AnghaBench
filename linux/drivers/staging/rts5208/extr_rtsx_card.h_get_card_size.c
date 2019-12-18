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
struct sd_info {int sd_lock_status; } ;
struct rtsx_chip {int /*<<< orphan*/ * capacity; struct sd_info sd_card; } ;

/* Variables and functions */
 scalar_t__ SD_CARD ; 
 int SD_LOCKED ; 
 scalar_t__ get_lun_card (struct rtsx_chip*,unsigned int) ; 

__attribute__((used)) static inline u32 get_card_size(struct rtsx_chip *chip, unsigned int lun)
{
#ifdef SUPPORT_SD_LOCK
	struct sd_info *sd_card = &chip->sd_card;

	if ((get_lun_card(chip, lun) == SD_CARD) &&
	    (sd_card->sd_lock_status & SD_LOCKED))
		return 0;

	return chip->capacity[lun];
#else
	return chip->capacity[lun];
#endif
}