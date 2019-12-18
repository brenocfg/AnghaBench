#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; } ;
struct spi_nor {int /*<<< orphan*/  spimem; TYPE_1__ mtd; } ;
struct TYPE_4__ {int nbytes; } ;
struct spi_mem_op {TYPE_2__ addr; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ SZ_16M ; 
 int /*<<< orphan*/  spi_mem_supports_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 

__attribute__((used)) static int spi_nor_spimem_check_op(struct spi_nor *nor,
				   struct spi_mem_op *op)
{
	/*
	 * First test with 4 address bytes. The opcode itself might
	 * be a 3B addressing opcode but we don't care, because
	 * SPI controller implementation should not check the opcode,
	 * but just the sequence.
	 */
	op->addr.nbytes = 4;
	if (!spi_mem_supports_op(nor->spimem, op)) {
		if (nor->mtd.size > SZ_16M)
			return -ENOTSUPP;

		/* If flash size <= 16MB, 3 address bytes are sufficient */
		op->addr.nbytes = 3;
		if (!spi_mem_supports_op(nor->spimem, op))
			return -ENOTSUPP;
	}

	return 0;
}