#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ delay_write_flag; } ;
struct ms_info {scalar_t__ cleanup_counter; TYPE_1__ delay_write; scalar_t__ seq_mode; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MSHG (struct ms_info*) ; 
 scalar_t__ CHK_MSPRO (struct ms_info*) ; 
 int /*<<< orphan*/  MS_2K_SECTOR_MODE ; 
 int /*<<< orphan*/  MS_CFG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ms_delay_write (struct rtsx_chip*) ; 
 int /*<<< orphan*/  mspro_stop_seq_mode (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ms_cleanup_work(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;

	if (CHK_MSPRO(ms_card)) {
		if (ms_card->seq_mode) {
			dev_dbg(rtsx_dev(chip), "MS Pro: stop transmission\n");
			mspro_stop_seq_mode(chip);
			ms_card->cleanup_counter = 0;
		}
		if (CHK_MSHG(ms_card)) {
			rtsx_write_register(chip, MS_CFG,
					    MS_2K_SECTOR_MODE, 0x00);
		}
	}
#ifdef MS_DELAY_WRITE
	else if ((!CHK_MSPRO(ms_card)) &&
		 ms_card->delay_write.delay_write_flag) {
		dev_dbg(rtsx_dev(chip), "MS: delay write\n");
		ms_delay_write(chip);
		ms_card->cleanup_counter = 0;
	}
#endif
}