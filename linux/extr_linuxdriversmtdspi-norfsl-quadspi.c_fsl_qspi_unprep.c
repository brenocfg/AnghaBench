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
struct spi_nor {struct fsl_qspi* priv; } ;
struct fsl_qspi {int /*<<< orphan*/  lock; } ;
typedef  enum spi_nor_ops { ____Placeholder_spi_nor_ops } spi_nor_ops ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_qspi_clk_disable_unprep (struct fsl_qspi*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_qspi_unprep(struct spi_nor *nor, enum spi_nor_ops ops)
{
	struct fsl_qspi *q = nor->priv;

	fsl_qspi_clk_disable_unprep(q);
	mutex_unlock(&q->lock);
}