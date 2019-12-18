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
typedef  int u8 ;
typedef  int u16 ;
struct spi_nor {struct intel_spi* priv; } ;
struct intel_spi {int atomic_preopcode; scalar_t__ swseq_reg; scalar_t__ base; scalar_t__ sregs; scalar_t__ locked; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FADDR ; 
 int /*<<< orphan*/  OPTYPE_WRITE_NO_ADDR ; 
 scalar_t__ PREOP_OPTYPE ; 
 int SPINOR_OP_WREN ; 
 int intel_spi_hw_cycle (struct intel_spi*,int,int) ; 
 int intel_spi_sw_cycle (struct intel_spi*,int,int,int /*<<< orphan*/ ) ; 
 int intel_spi_write_block (struct intel_spi*,int*,int) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int intel_spi_write_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	struct intel_spi *ispi = nor->priv;
	int ret;

	/*
	 * This is handled with atomic operation and preop code in Intel
	 * controller so we only verify that it is available. If the
	 * controller is not locked, program the opcode to the PREOP
	 * register for later use.
	 *
	 * When hardware sequencer is used there is no need to program
	 * any opcodes (it handles them automatically as part of a command).
	 */
	if (opcode == SPINOR_OP_WREN) {
		u16 preop;

		if (!ispi->swseq_reg)
			return 0;

		preop = readw(ispi->sregs + PREOP_OPTYPE);
		if ((preop & 0xff) != opcode && (preop >> 8) != opcode) {
			if (ispi->locked)
				return -EINVAL;
			writel(opcode, ispi->sregs + PREOP_OPTYPE);
		}

		/*
		 * This enables atomic sequence on next SW sycle. Will
		 * be cleared after next operation.
		 */
		ispi->atomic_preopcode = opcode;
		return 0;
	}

	writel(0, ispi->base + FADDR);

	/* Write the value beforehand */
	ret = intel_spi_write_block(ispi, buf, len);
	if (ret)
		return ret;

	if (ispi->swseq_reg)
		return intel_spi_sw_cycle(ispi, opcode, len,
					  OPTYPE_WRITE_NO_ADDR);
	return intel_spi_hw_cycle(ispi, opcode, len);
}