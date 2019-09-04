#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int size; int strength; int bytes; } ;
struct TYPE_4__ {TYPE_1__ ecc; } ;
struct omap_nand_info {TYPE_2__ nand; } ;

/* Variables and functions */
 scalar_t__ hweight8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int erased_sector_bitflips(u_char *data, u_char *oob,
		struct omap_nand_info *info)
{
	int flip_bits = 0, i;

	for (i = 0; i < info->nand.ecc.size; i++) {
		flip_bits += hweight8(~data[i]);
		if (flip_bits > info->nand.ecc.strength)
			return 0;
	}

	for (i = 0; i < info->nand.ecc.bytes - 1; i++) {
		flip_bits += hweight8(~oob[i]);
		if (flip_bits > info->nand.ecc.strength)
			return 0;
	}

	/*
	 * Bit flips falls in correctable level.
	 * Fill data area with 0xFF
	 */
	if (flip_bits) {
		memset(data, 0xFF, info->nand.ecc.size);
		memset(oob, 0xFF, info->nand.ecc.bytes);
	}

	return flip_bits;
}