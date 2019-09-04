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
struct onenand_chip {int density_mask; } ;

/* Variables and functions */
 int ONENAND_DDP_CHIP1 ; 

__attribute__((used)) static int onenand_block_address(struct onenand_chip *this, int block)
{
	/* Device Flash Core select, NAND Flash Block Address */
	if (block & this->density_mask)
		return ONENAND_DDP_CHIP1 | (block ^ this->density_mask);

	return block;
}