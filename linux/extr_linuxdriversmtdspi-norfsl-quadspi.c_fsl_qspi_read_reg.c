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
struct spi_nor {struct fsl_qspi* priv; } ;
struct fsl_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_qspi_read_data (struct fsl_qspi*,int,int /*<<< orphan*/ *) ; 
 int fsl_qspi_runcmd (struct fsl_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsl_qspi_read_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	int ret;
	struct fsl_qspi *q = nor->priv;

	ret = fsl_qspi_runcmd(q, opcode, 0, len);
	if (ret)
		return ret;

	fsl_qspi_read_data(q, len, buf);
	return 0;
}