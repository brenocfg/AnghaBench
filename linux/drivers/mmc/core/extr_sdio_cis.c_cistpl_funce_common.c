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
struct sdio_func {int dummy; } ;
struct TYPE_2__ {unsigned char blksize; int max_dtr; } ;
struct mmc_card {TYPE_1__ cis; } ;

/* Variables and functions */
 int EINVAL ; 
 int* speed_unit ; 
 int* speed_val ; 

__attribute__((used)) static int cistpl_funce_common(struct mmc_card *card, struct sdio_func *func,
			       const unsigned char *buf, unsigned size)
{
	/* Only valid for the common CIS (function 0) */
	if (func)
		return -EINVAL;

	/* TPLFE_FN0_BLK_SIZE */
	card->cis.blksize = buf[1] | (buf[2] << 8);

	/* TPLFE_MAX_TRAN_SPEED */
	card->cis.max_dtr = speed_val[(buf[3] >> 3) & 15] *
			    speed_unit[buf[3] & 7];

	return 0;
}