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
struct spi_nor {int (* read_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ;int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPINOR_OP_RDSR2 ; 
 int /*<<< orphan*/  SPINOR_OP_WRSR2 ; 
 int SR2_QUAD_EN_BIT7 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int spi_nor_wait_till_ready (struct spi_nor*) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 
 int stub2 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 
 int stub3 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static int sr2_bit7_quad_enable(struct spi_nor *nor)
{
	u8 sr2;
	int ret;

	/* Check current Quad Enable bit value. */
	ret = nor->read_reg(nor, SPINOR_OP_RDSR2, &sr2, 1);
	if (ret)
		return ret;
	if (sr2 & SR2_QUAD_EN_BIT7)
		return 0;

	/* Update the Quad Enable bit. */
	sr2 |= SR2_QUAD_EN_BIT7;

	write_enable(nor);

	ret = nor->write_reg(nor, SPINOR_OP_WRSR2, &sr2, 1);
	if (ret < 0) {
		dev_err(nor->dev, "error while writing status register 2\n");
		return -EINVAL;
	}

	ret = spi_nor_wait_till_ready(nor);
	if (ret < 0) {
		dev_err(nor->dev, "timeout while writing status register 2\n");
		return ret;
	}

	/* Read back and check it. */
	ret = nor->read_reg(nor, SPINOR_OP_RDSR2, &sr2, 1);
	if (!(ret > 0 && (sr2 & SR2_QUAD_EN_BIT7))) {
		dev_err(nor->dev, "SR2 Quad bit not set\n");
		return -EINVAL;
	}

	return 0;
}