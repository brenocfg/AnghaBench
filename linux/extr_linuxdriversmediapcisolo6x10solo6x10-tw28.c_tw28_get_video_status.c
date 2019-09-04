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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TW286x_AV_STAT_ADDR ; 
 int /*<<< orphan*/  TW_AV_STAT_ADDR ; 
 int tw_readbyte (struct solo_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tw28_get_video_status(struct solo_dev *solo_dev, u8 ch)
{
	u8 val, chip_num;

	/* Get the right chip and on-chip channel */
	chip_num = ch / 4;
	ch %= 4;

	val = tw_readbyte(solo_dev, chip_num, TW286x_AV_STAT_ADDR,
			  TW_AV_STAT_ADDR) & 0x0f;

	return val & (1 << ch) ? 1 : 0;
}