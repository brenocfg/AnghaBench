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
struct socrates_nand_host {int /*<<< orphan*/  io_base; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int FPGA_NAND_BUSY ; 
 int in_be32 (int /*<<< orphan*/ ) ; 
 struct socrates_nand_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int socrates_nand_device_ready(struct nand_chip *nand_chip)
{
	struct socrates_nand_host *host = nand_get_controller_data(nand_chip);

	if (in_be32(host->io_base) & FPGA_NAND_BUSY)
		return 0; /* busy */
	return 1;
}