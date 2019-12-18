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
typedef  int u32 ;
struct spi_nor_read_command {scalar_t__ num_wait_states; scalar_t__ num_mode_clocks; int /*<<< orphan*/  proto; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {struct spi_nor_read_command* reads; } ;
struct spi_nor {scalar_t__ read_dummy; int /*<<< orphan*/  read_proto; int /*<<< orphan*/  read_opcode; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int SNOR_HWCAPS_READ_MASK ; 
 int fls (int) ; 
 int spi_nor_hwcaps_read2cmd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_nor_select_read(struct spi_nor *nor,
			       u32 shared_hwcaps)
{
	int cmd, best_match = fls(shared_hwcaps & SNOR_HWCAPS_READ_MASK) - 1;
	const struct spi_nor_read_command *read;

	if (best_match < 0)
		return -EINVAL;

	cmd = spi_nor_hwcaps_read2cmd(BIT(best_match));
	if (cmd < 0)
		return -EINVAL;

	read = &nor->params.reads[cmd];
	nor->read_opcode = read->opcode;
	nor->read_proto = read->proto;

	/*
	 * In the spi-nor framework, we don't need to make the difference
	 * between mode clock cycles and wait state clock cycles.
	 * Indeed, the value of the mode clock cycles is used by a QSPI
	 * flash memory to know whether it should enter or leave its 0-4-4
	 * (Continuous Read / XIP) mode.
	 * eXecution In Place is out of the scope of the mtd sub-system.
	 * Hence we choose to merge both mode and wait state clock cycles
	 * into the so called dummy clock cycles.
	 */
	nor->read_dummy = read->num_mode_clocks + read->num_wait_states;
	return 0;
}