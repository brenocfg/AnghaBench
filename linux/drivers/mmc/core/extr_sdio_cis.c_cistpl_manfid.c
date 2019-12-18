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
struct sdio_func {unsigned int vendor; unsigned int device; } ;
struct TYPE_2__ {unsigned int vendor; unsigned int device; } ;
struct mmc_card {TYPE_1__ cis; } ;

/* Variables and functions */

__attribute__((used)) static int cistpl_manfid(struct mmc_card *card, struct sdio_func *func,
			 const unsigned char *buf, unsigned size)
{
	unsigned int vendor, device;

	/* TPLMID_MANF */
	vendor = buf[0] | (buf[1] << 8);

	/* TPLMID_CARD */
	device = buf[2] | (buf[3] << 8);

	if (func) {
		func->vendor = vendor;
		func->device = device;
	} else {
		card->cis.vendor = vendor;
		card->cis.device = device;
	}

	return 0;
}