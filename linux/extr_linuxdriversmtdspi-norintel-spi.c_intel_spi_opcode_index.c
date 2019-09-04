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
typedef  scalar_t__ u8 ;
struct intel_spi {scalar_t__* opcodes; scalar_t__ sregs; scalar_t__ locked; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 scalar_t__ OPMENU0 ; 
 scalar_t__ PREOP_OPTYPE ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int intel_spi_opcode_index(struct intel_spi *ispi, u8 opcode, int optype)
{
	int i;
	int preop;

	if (ispi->locked) {
		for (i = 0; i < ARRAY_SIZE(ispi->opcodes); i++)
			if (ispi->opcodes[i] == opcode)
				return i;

		return -EINVAL;
	}

	/* The lock is off, so just use index 0 */
	writel(opcode, ispi->sregs + OPMENU0);
	preop = readw(ispi->sregs + PREOP_OPTYPE);
	writel(optype << 16 | preop, ispi->sregs + PREOP_OPTYPE);

	return 0;
}