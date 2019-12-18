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
struct TYPE_2__ {unsigned long* cache; } ;
struct nand_device {TYPE_1__ bbt; } ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 int ERANGE ; 
 unsigned long GENMASK (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_BBT_BLOCK_NUM_STATUS ; 
 unsigned int fls (int /*<<< orphan*/ ) ; 
 unsigned int nanddev_neraseblocks (struct nand_device const*) ; 

int nanddev_bbt_get_block_status(const struct nand_device *nand,
				 unsigned int entry)
{
	unsigned int bits_per_block = fls(NAND_BBT_BLOCK_NUM_STATUS);
	unsigned long *pos = nand->bbt.cache +
			     ((entry * bits_per_block) / BITS_PER_LONG);
	unsigned int offs = (entry * bits_per_block) % BITS_PER_LONG;
	unsigned long status;

	if (entry >= nanddev_neraseblocks(nand))
		return -ERANGE;

	status = pos[0] >> offs;
	if (bits_per_block + offs > BITS_PER_LONG)
		status |= pos[1] << (BITS_PER_LONG - offs);

	return status & GENMASK(bits_per_block - 1, 0);
}