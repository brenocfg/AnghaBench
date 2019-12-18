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
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ath9k_hw_nvram_read (struct ath_hw*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ar9300_eeprom_restore_flash(struct ath_hw *ah, u8 *mptr,
				       int mdata_size)
{
	u16 *data = (u16 *) mptr;
	int i;

	for (i = 0; i < mdata_size / 2; i++, data++)
		if (!ath9k_hw_nvram_read(ah, i, data))
			return -EIO;

	return 0;
}