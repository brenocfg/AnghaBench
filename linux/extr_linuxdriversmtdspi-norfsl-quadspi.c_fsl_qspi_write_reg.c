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
typedef  int /*<<< orphan*/  u32 ;
struct spi_nor {struct fsl_qspi* priv; } ;
struct fsl_qspi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPINOR_OP_CHIP_ERASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_qspi_invalid (struct fsl_qspi*) ; 
 int fsl_qspi_nor_write (struct fsl_qspi*,struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fsl_qspi_runcmd (struct fsl_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsl_qspi_write_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	struct fsl_qspi *q = nor->priv;
	int ret;

	if (!buf) {
		ret = fsl_qspi_runcmd(q, opcode, 0, 1);
		if (ret)
			return ret;

		if (opcode == SPINOR_OP_CHIP_ERASE)
			fsl_qspi_invalid(q);

	} else if (len > 0) {
		ret = fsl_qspi_nor_write(q, nor, opcode, 0,
					(u32 *)buf, len);
		if (ret > 0)
			return 0;
	} else {
		dev_err(q->dev, "invalid cmd %d\n", opcode);
		ret = -EINVAL;
	}

	return ret;
}