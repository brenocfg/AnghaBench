#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int erasesize; } ;
struct spi_nor {int /*<<< orphan*/  erase_opcode; TYPE_1__ mtd; int /*<<< orphan*/  dev; struct fsl_qspi* priv; } ;
struct fsl_qspi {int /*<<< orphan*/  chip_base_addr; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_qspi_invalid (struct fsl_qspi*) ; 
 int fsl_qspi_runcmd (struct fsl_qspi*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_qspi_erase(struct spi_nor *nor, loff_t offs)
{
	struct fsl_qspi *q = nor->priv;
	int ret;

	dev_dbg(nor->dev, "%dKiB at 0x%08x:0x%08x\n",
		nor->mtd.erasesize / 1024, q->chip_base_addr, (u32)offs);

	ret = fsl_qspi_runcmd(q, nor->erase_opcode, offs, 0);
	if (ret)
		return ret;

	fsl_qspi_invalid(q);
	return 0;
}