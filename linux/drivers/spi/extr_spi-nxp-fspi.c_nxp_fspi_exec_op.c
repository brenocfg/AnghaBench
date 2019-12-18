#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nbytes; scalar_t__ dir; } ;
struct spi_mem_op {TYPE_2__ data; } ;
struct spi_mem {TYPE_3__* spi; } ;
struct nxp_fspi {int /*<<< orphan*/  lock; TYPE_1__* devtype_data; scalar_t__ iobase; } ;
struct TYPE_6__ {int /*<<< orphan*/  master; } ;
struct TYPE_4__ {int rxfifo; } ;

/* Variables and functions */
 scalar_t__ FSPI_STS0 ; 
 int /*<<< orphan*/  FSPI_STS0_ARB_IDLE ; 
 int /*<<< orphan*/  POLL_TOUT ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 scalar_t__ SPI_MEM_DATA_OUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fspi_readl_poll_tout (struct nxp_fspi*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nxp_fspi_do_op (struct nxp_fspi*,struct spi_mem_op const*) ; 
 int /*<<< orphan*/  nxp_fspi_fill_txfifo (struct nxp_fspi*,struct spi_mem_op const*) ; 
 int /*<<< orphan*/  nxp_fspi_invalid (struct nxp_fspi*) ; 
 int /*<<< orphan*/  nxp_fspi_prepare_lut (struct nxp_fspi*,struct spi_mem_op const*) ; 
 int /*<<< orphan*/  nxp_fspi_read_ahb (struct nxp_fspi*,struct spi_mem_op const*) ; 
 int /*<<< orphan*/  nxp_fspi_select_mem (struct nxp_fspi*,TYPE_3__*) ; 
 struct nxp_fspi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxp_fspi_exec_op(struct spi_mem *mem, const struct spi_mem_op *op)
{
	struct nxp_fspi *f = spi_controller_get_devdata(mem->spi->master);
	int err = 0;

	mutex_lock(&f->lock);

	/* Wait for controller being ready. */
	err = fspi_readl_poll_tout(f, f->iobase + FSPI_STS0,
				   FSPI_STS0_ARB_IDLE, 1, POLL_TOUT, true);
	WARN_ON(err);

	nxp_fspi_select_mem(f, mem->spi);

	nxp_fspi_prepare_lut(f, op);
	/*
	 * If we have large chunks of data, we read them through the AHB bus
	 * by accessing the mapped memory. In all other cases we use
	 * IP commands to access the flash.
	 */
	if (op->data.nbytes > (f->devtype_data->rxfifo - 4) &&
	    op->data.dir == SPI_MEM_DATA_IN) {
		nxp_fspi_read_ahb(f, op);
	} else {
		if (op->data.nbytes && op->data.dir == SPI_MEM_DATA_OUT)
			nxp_fspi_fill_txfifo(f, op);

		err = nxp_fspi_do_op(f, op);
	}

	/* Invalidate the data in the AHB buffer. */
	nxp_fspi_invalid(f);

	mutex_unlock(&f->lock);

	return err;
}