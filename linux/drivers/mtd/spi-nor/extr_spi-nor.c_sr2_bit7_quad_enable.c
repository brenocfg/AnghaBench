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
struct spi_nor {int* bouncebuf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SR2_QUAD_EN_BIT7 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int spi_nor_read_sr2 (struct spi_nor*,int*) ; 
 int spi_nor_wait_till_ready (struct spi_nor*) ; 
 int spi_nor_write_sr2 (struct spi_nor*,int*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static int sr2_bit7_quad_enable(struct spi_nor *nor)
{
	u8 *sr2 = nor->bouncebuf;
	int ret;

	/* Check current Quad Enable bit value. */
	ret = spi_nor_read_sr2(nor, sr2);
	if (ret)
		return ret;
	if (*sr2 & SR2_QUAD_EN_BIT7)
		return 0;

	/* Update the Quad Enable bit. */
	*sr2 |= SR2_QUAD_EN_BIT7;

	write_enable(nor);

	ret = spi_nor_write_sr2(nor, sr2);
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
	ret = spi_nor_read_sr2(nor, sr2);
	if (!(ret > 0 && (*sr2 & SR2_QUAD_EN_BIT7))) {
		dev_err(nor->dev, "SR2 Quad bit not set\n");
		return -EINVAL;
	}

	return 0;
}