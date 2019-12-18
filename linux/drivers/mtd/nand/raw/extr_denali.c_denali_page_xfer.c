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
struct nand_chip {int /*<<< orphan*/  cur_cs; } ;
struct denali_controller {scalar_t__ dma_avail; } ;

/* Variables and functions */
 int denali_dma_xfer (struct denali_controller*,void*,size_t,int,int) ; 
 int denali_pio_xfer (struct denali_controller*,void*,size_t,int,int) ; 
 int /*<<< orphan*/  denali_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct denali_controller* to_denali_controller (struct nand_chip*) ; 

__attribute__((used)) static int denali_page_xfer(struct nand_chip *chip, void *buf, size_t size,
			    int page, bool write)
{
	struct denali_controller *denali = to_denali_controller(chip);

	denali_select_target(chip, chip->cur_cs);

	if (denali->dma_avail)
		return denali_dma_xfer(denali, buf, size, page, write);
	else
		return denali_pio_xfer(denali, buf, size, page, write);
}