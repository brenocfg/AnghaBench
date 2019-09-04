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
 int fsl_qspi_clk_prep_enable (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_set_base_addr (struct fsl_qspi*,struct spi_nor*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_qspi_prep(struct spi_nor *nor, enum spi_nor_ops ops)
{
	struct fsl_qspi *q = nor->priv;
	int ret;

	mutex_lock(&q->lock);

	ret = fsl_qspi_clk_prep_enable(q);
	if (ret)
		goto err_mutex;

	fsl_qspi_set_base_addr(q, nor);
	return 0;

err_mutex:
	mutex_unlock(&q->lock);
	return ret;
}