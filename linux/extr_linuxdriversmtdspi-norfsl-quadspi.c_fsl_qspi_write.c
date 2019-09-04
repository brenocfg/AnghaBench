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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_nor {int /*<<< orphan*/  program_opcode; struct fsl_qspi* priv; } ;
struct fsl_qspi {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_qspi_invalid (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_nor_write (struct fsl_qspi*,struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t fsl_qspi_write(struct spi_nor *nor, loff_t to,
			      size_t len, const u_char *buf)
{
	struct fsl_qspi *q = nor->priv;
	ssize_t ret = fsl_qspi_nor_write(q, nor, nor->program_opcode, to,
					 (u32 *)buf, len);

	/* invalid the data in the AHB buffer. */
	fsl_qspi_invalid(q);
	return ret;
}