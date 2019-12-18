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
struct nand_pos {int dummy; } ;
struct nand_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* isbad ) (struct nand_device*,struct nand_pos const*) ;} ;

/* Variables and functions */
 int NAND_BBT_BLOCK_FACTORY_BAD ; 
 int NAND_BBT_BLOCK_GOOD ; 
 int NAND_BBT_BLOCK_STATUS_UNKNOWN ; 
 int NAND_BBT_BLOCK_WORN ; 
 int nanddev_bbt_get_block_status (struct nand_device*,unsigned int) ; 
 scalar_t__ nanddev_bbt_is_initialized (struct nand_device*) ; 
 unsigned int nanddev_bbt_pos_to_entry (struct nand_device*,struct nand_pos const*) ; 
 int /*<<< orphan*/  nanddev_bbt_set_block_status (struct nand_device*,unsigned int,int) ; 
 int stub1 (struct nand_device*,struct nand_pos const*) ; 
 int stub2 (struct nand_device*,struct nand_pos const*) ; 

bool nanddev_isbad(struct nand_device *nand, const struct nand_pos *pos)
{
	if (nanddev_bbt_is_initialized(nand)) {
		unsigned int entry;
		int status;

		entry = nanddev_bbt_pos_to_entry(nand, pos);
		status = nanddev_bbt_get_block_status(nand, entry);
		/* Lazy block status retrieval */
		if (status == NAND_BBT_BLOCK_STATUS_UNKNOWN) {
			if (nand->ops->isbad(nand, pos))
				status = NAND_BBT_BLOCK_FACTORY_BAD;
			else
				status = NAND_BBT_BLOCK_GOOD;

			nanddev_bbt_set_block_status(nand, entry, status);
		}

		if (status == NAND_BBT_BLOCK_WORN ||
		    status == NAND_BBT_BLOCK_FACTORY_BAD)
			return true;

		return false;
	}

	return nand->ops->isbad(nand, pos);
}