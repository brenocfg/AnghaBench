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
struct onenand_chip {int page_shift; scalar_t__ base; int /*<<< orphan*/  (* write_word ) (int,scalar_t__) ;TYPE_1__* bufferram; } ;
struct mtd_info {struct onenand_chip* priv; } ;
typedef  int loff_t ;
struct TYPE_2__ {int blockpage; } ;

/* Variables and functions */
 unsigned int ONENAND_CURRENT_BUFFERRAM (struct onenand_chip*) ; 
 scalar_t__ ONENAND_IS_2PLANE (struct onenand_chip*) ; 
 scalar_t__ ONENAND_IS_DDP (struct onenand_chip*) ; 
 unsigned int ONENAND_NEXT_BUFFERRAM (struct onenand_chip*) ; 
 scalar_t__ ONENAND_REG_START_ADDRESS2 ; 
 int /*<<< orphan*/  ONENAND_SET_NEXT_BUFFERRAM (struct onenand_chip*) ; 
 int onenand_block (struct onenand_chip*,int) ; 
 int onenand_bufferram_address (struct onenand_chip*,int) ; 
 int onenand_get_2x_blockpage (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__) ; 

__attribute__((used)) static int onenand_check_bufferram(struct mtd_info *mtd, loff_t addr)
{
	struct onenand_chip *this = mtd->priv;
	int blockpage, found = 0;
	unsigned int i;

	if (ONENAND_IS_2PLANE(this))
		blockpage = onenand_get_2x_blockpage(mtd, addr);
	else
		blockpage = (int) (addr >> this->page_shift);

	/* Is there valid data? */
	i = ONENAND_CURRENT_BUFFERRAM(this);
	if (this->bufferram[i].blockpage == blockpage)
		found = 1;
	else {
		/* Check another BufferRAM */
		i = ONENAND_NEXT_BUFFERRAM(this);
		if (this->bufferram[i].blockpage == blockpage) {
			ONENAND_SET_NEXT_BUFFERRAM(this);
			found = 1;
		}
	}

	if (found && ONENAND_IS_DDP(this)) {
		/* Select DataRAM for DDP */
		int block = onenand_block(this, addr);
		int value = onenand_bufferram_address(this, block);
		this->write_word(value, this->base + ONENAND_REG_START_ADDRESS2);
	}

	return found;
}