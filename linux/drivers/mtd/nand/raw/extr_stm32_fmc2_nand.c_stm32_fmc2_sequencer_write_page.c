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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/  cur_cs; } ;

/* Variables and functions */
 int stm32_fmc2_select_chip (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int stm32_fmc2_sequencer_write (struct nand_chip*,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static int stm32_fmc2_sequencer_write_page(struct nand_chip *chip,
					   const u8 *buf,
					   int oob_required,
					   int page)
{
	int ret;

	/* Select the target */
	ret = stm32_fmc2_select_chip(chip, chip->cur_cs);
	if (ret)
		return ret;

	return stm32_fmc2_sequencer_write(chip, buf, oob_required, page, false);
}