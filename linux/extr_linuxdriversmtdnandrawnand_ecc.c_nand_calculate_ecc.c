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
struct mtd_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nand_calculate_ecc (unsigned char const*,int /*<<< orphan*/ ,unsigned char*) ; 
 TYPE_2__* mtd_to_nand (struct mtd_info*) ; 

int nand_calculate_ecc(struct mtd_info *mtd, const unsigned char *buf,
		       unsigned char *code)
{
	__nand_calculate_ecc(buf,
			mtd_to_nand(mtd)->ecc.size, code);

	return 0;
}