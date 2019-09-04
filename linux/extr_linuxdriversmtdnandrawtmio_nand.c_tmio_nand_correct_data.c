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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int __nand_correct_data (unsigned char*,unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int tmio_nand_correct_data(struct mtd_info *mtd, unsigned char *buf,
		unsigned char *read_ecc, unsigned char *calc_ecc)
{
	int r0, r1;

	/* assume ecc.size = 512 and ecc.bytes = 6 */
	r0 = __nand_correct_data(buf, read_ecc, calc_ecc, 256);
	if (r0 < 0)
		return r0;
	r1 = __nand_correct_data(buf + 256, read_ecc + 3, calc_ecc + 3, 256);
	if (r1 < 0)
		return r1;
	return r0 + r1;
}