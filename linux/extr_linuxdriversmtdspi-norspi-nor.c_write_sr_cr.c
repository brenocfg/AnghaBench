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
struct spi_nor {int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPINOR_OP_WRSR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int spi_nor_wait_till_ready (struct spi_nor*) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static int write_sr_cr(struct spi_nor *nor, u8 *sr_cr)
{
	int ret;

	write_enable(nor);

	ret = nor->write_reg(nor, SPINOR_OP_WRSR, sr_cr, 2);
	if (ret < 0) {
		dev_err(nor->dev,
			"error while writing configuration register\n");
		return -EINVAL;
	}

	ret = spi_nor_wait_till_ready(nor);
	if (ret) {
		dev_err(nor->dev,
			"timeout while writing configuration register\n");
		return ret;
	}

	return 0;
}