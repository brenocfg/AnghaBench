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
struct nand_chip {int options; } ;

/* Variables and functions */
 int NAND_BROKEN_XD ; 
 int NAND_STATUS_WP ; 
 int nand_status_op (struct nand_chip*,int*) ; 

__attribute__((used)) static int nand_check_wp(struct nand_chip *chip)
{
	u8 status;
	int ret;

	/* Broken xD cards report WP despite being writable */
	if (chip->options & NAND_BROKEN_XD)
		return 0;

	/* Check the WP bit */
	ret = nand_status_op(chip, &status);
	if (ret)
		return ret;

	return status & NAND_STATUS_WP ? 0 : 1;
}