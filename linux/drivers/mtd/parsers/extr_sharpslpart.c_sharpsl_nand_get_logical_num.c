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
typedef  int u16 ;

/* Variables and functions */
 int BLOCK_IS_RESERVED ; 
 int BLOCK_UNMASK_COMPLEMENT ; 
 int EINVAL ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 size_t NAND_NOOB_LOGADDR_00 ; 
 size_t NAND_NOOB_LOGADDR_01 ; 
 size_t NAND_NOOB_LOGADDR_10 ; 
 size_t NAND_NOOB_LOGADDR_11 ; 
 size_t NAND_NOOB_LOGADDR_20 ; 
 size_t NAND_NOOB_LOGADDR_21 ; 
 int hweight16 (int) ; 

__attribute__((used)) static int sharpsl_nand_get_logical_num(u8 *oob)
{
	u16 us;
	int good0, good1;

	if (oob[NAND_NOOB_LOGADDR_00] == oob[NAND_NOOB_LOGADDR_10] &&
	    oob[NAND_NOOB_LOGADDR_01] == oob[NAND_NOOB_LOGADDR_11]) {
		good0 = NAND_NOOB_LOGADDR_00;
		good1 = NAND_NOOB_LOGADDR_01;
	} else if (oob[NAND_NOOB_LOGADDR_10] == oob[NAND_NOOB_LOGADDR_20] &&
		   oob[NAND_NOOB_LOGADDR_11] == oob[NAND_NOOB_LOGADDR_21]) {
		good0 = NAND_NOOB_LOGADDR_10;
		good1 = NAND_NOOB_LOGADDR_11;
	} else if (oob[NAND_NOOB_LOGADDR_20] == oob[NAND_NOOB_LOGADDR_00] &&
		   oob[NAND_NOOB_LOGADDR_21] == oob[NAND_NOOB_LOGADDR_01]) {
		good0 = NAND_NOOB_LOGADDR_20;
		good1 = NAND_NOOB_LOGADDR_21;
	} else {
		return -EINVAL;
	}

	us = oob[good0] | oob[good1] << 8;

	/* parity check */
	if (hweight16(us) & BLOCK_UNMASK_COMPLEMENT)
		return -EINVAL;

	/* reserved */
	if (us == BLOCK_IS_RESERVED)
		return BLOCK_IS_RESERVED;

	return (us >> 1) & GENMASK(9, 0);
}