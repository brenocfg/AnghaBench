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
struct mtd_info {int oobsize; int writesize; } ;

/* Variables and functions */

__attribute__((used)) static int get_eccsize(struct mtd_info *mtd)
{
	int oobbytes_per_512 = 0;

	oobbytes_per_512 = mtd->oobsize * 512 / mtd->writesize;

	if (oobbytes_per_512 < 26)
		return 4;
	else
		return 8;
}