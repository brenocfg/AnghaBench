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
struct spi_nor {struct cqspi_flash_pdata* priv; } ;
struct cqspi_st {int /*<<< orphan*/  bus_mutex; } ;
struct cqspi_flash_pdata {struct cqspi_st* cqspi; } ;
typedef  enum spi_nor_ops { ____Placeholder_spi_nor_ops } spi_nor_ops ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cqspi_unprep(struct spi_nor *nor, enum spi_nor_ops ops)
{
	struct cqspi_flash_pdata *f_pdata = nor->priv;
	struct cqspi_st *cqspi = f_pdata->cqspi;

	mutex_unlock(&cqspi->bus_mutex);
}