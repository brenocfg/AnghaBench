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
typedef  int uint8_t ;
struct socrates_nand_host {int /*<<< orphan*/  io_base; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int const FPGA_NAND_CMD_WRITE ; 
 int const FPGA_NAND_DATA_SHIFT ; 
 int const FPGA_NAND_ENABLE ; 
 struct socrates_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void socrates_nand_write_buf(struct nand_chip *this, const uint8_t *buf,
				    int len)
{
	int i;
	struct socrates_nand_host *host = nand_get_controller_data(this);

	for (i = 0; i < len; i++) {
		out_be32(host->io_base, FPGA_NAND_ENABLE |
				FPGA_NAND_CMD_WRITE |
				(buf[i] << FPGA_NAND_DATA_SHIFT));
	}
}