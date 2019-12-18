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
struct spinand_device {int /*<<< orphan*/  spimem; int /*<<< orphan*/ * scratchbuf; } ;
struct spi_mem_op {int dummy; } ;

/* Variables and functions */
 struct spi_mem_op SPINAND_SET_FEATURE_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 

__attribute__((used)) static int spinand_write_reg_op(struct spinand_device *spinand, u8 reg, u8 val)
{
	struct spi_mem_op op = SPINAND_SET_FEATURE_OP(reg,
						      spinand->scratchbuf);

	*spinand->scratchbuf = val;
	return spi_mem_exec_op(spinand->spimem, &op);
}