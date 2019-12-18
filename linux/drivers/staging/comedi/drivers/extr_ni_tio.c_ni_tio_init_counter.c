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
struct ni_gpct_device {int** regs; } ;
struct ni_gpct {unsigned int counter_index; unsigned int chip_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int GI_SYNC_GATE ; 
 size_t NITIO_AUTO_INC_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_CMD_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_CNT_MODE_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_DMA_CFG_REG (unsigned int) ; 
 size_t NITIO_GATE2_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_INPUT_SEL_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_INT_ENA_REG (unsigned int) ; 
 size_t NITIO_LOADA_REG (unsigned int) ; 
 size_t NITIO_LOADB_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_MODE_REG (unsigned int) ; 
 scalar_t__ ni_tio_counting_mode_registers_present (struct ni_gpct_device*) ; 
 scalar_t__ ni_tio_has_gate2_registers (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_reset_count_and_disarm (struct ni_gpct*) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ni_tio_write (struct ni_gpct*,int,size_t) ; 

void ni_tio_init_counter(struct ni_gpct *counter)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int chip = counter->chip_index;

	ni_tio_reset_count_and_disarm(counter);

	/* initialize counter registers */
	counter_dev->regs[chip][NITIO_AUTO_INC_REG(cidx)] = 0x0;
	ni_tio_write(counter, 0x0, NITIO_AUTO_INC_REG(cidx));

	ni_tio_set_bits(counter, NITIO_CMD_REG(cidx),
			~0, GI_SYNC_GATE);

	ni_tio_set_bits(counter, NITIO_MODE_REG(cidx), ~0, 0);

	counter_dev->regs[chip][NITIO_LOADA_REG(cidx)] = 0x0;
	ni_tio_write(counter, 0x0, NITIO_LOADA_REG(cidx));

	counter_dev->regs[chip][NITIO_LOADB_REG(cidx)] = 0x0;
	ni_tio_write(counter, 0x0, NITIO_LOADB_REG(cidx));

	ni_tio_set_bits(counter, NITIO_INPUT_SEL_REG(cidx), ~0, 0);

	if (ni_tio_counting_mode_registers_present(counter_dev))
		ni_tio_set_bits(counter, NITIO_CNT_MODE_REG(cidx), ~0, 0);

	if (ni_tio_has_gate2_registers(counter_dev)) {
		counter_dev->regs[chip][NITIO_GATE2_REG(cidx)] = 0x0;
		ni_tio_write(counter, 0x0, NITIO_GATE2_REG(cidx));
	}

	ni_tio_set_bits(counter, NITIO_DMA_CFG_REG(cidx), ~0, 0x0);

	ni_tio_set_bits(counter, NITIO_INT_ENA_REG(cidx), ~0, 0x0);
}