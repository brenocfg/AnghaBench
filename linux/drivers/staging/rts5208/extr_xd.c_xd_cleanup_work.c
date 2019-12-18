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
struct xd_info {scalar_t__ cleanup_counter; TYPE_1__ delay_write; } ;
struct rtsx_chip {struct xd_info xd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  xd_delay_write (struct rtsx_chip*) ; 

void xd_cleanup_work(struct rtsx_chip *chip)
{
#ifdef XD_DELAY_WRITE
	struct xd_info *xd_card = &chip->xd_card;

	if (xd_card->delay_write.delay_write_flag) {
		dev_dbg(rtsx_dev(chip), "xD: delay write\n");
		xd_delay_write(chip);
		xd_card->cleanup_counter = 0;
	}
#endif
}