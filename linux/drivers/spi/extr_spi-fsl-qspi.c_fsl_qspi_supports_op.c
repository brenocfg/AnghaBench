#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ nbytes; int buswidth; scalar_t__ dir; } ;
struct TYPE_10__ {int nbytes; int buswidth; } ;
struct TYPE_9__ {int nbytes; int buswidth; } ;
struct TYPE_8__ {int buswidth; } ;
struct spi_mem_op {TYPE_5__ data; TYPE_4__ dummy; TYPE_3__ addr; TYPE_2__ cmd; } ;
struct spi_mem {TYPE_1__* spi; } ;
struct fsl_qspi {TYPE_6__* devtype_data; } ;
struct TYPE_12__ {scalar_t__ ahb_buf_size; int rxfifo; scalar_t__ txfifo; } ;
struct TYPE_7__ {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 scalar_t__ SPI_MEM_DATA_OUT ; 
 int fsl_qspi_check_buswidth (struct fsl_qspi*,int) ; 
 struct fsl_qspi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fsl_qspi_supports_op(struct spi_mem *mem,
				 const struct spi_mem_op *op)
{
	struct fsl_qspi *q = spi_controller_get_devdata(mem->spi->master);
	int ret;

	ret = fsl_qspi_check_buswidth(q, op->cmd.buswidth);

	if (op->addr.nbytes)
		ret |= fsl_qspi_check_buswidth(q, op->addr.buswidth);

	if (op->dummy.nbytes)
		ret |= fsl_qspi_check_buswidth(q, op->dummy.buswidth);

	if (op->data.nbytes)
		ret |= fsl_qspi_check_buswidth(q, op->data.buswidth);

	if (ret)
		return false;

	/*
	 * The number of instructions needed for the op, needs
	 * to fit into a single LUT entry.
	 */
	if (op->addr.nbytes +
	   (op->dummy.nbytes ? 1:0) +
	   (op->data.nbytes ? 1:0) > 6)
		return false;

	/* Max 64 dummy clock cycles supported */
	if (op->dummy.nbytes &&
	    (op->dummy.nbytes * 8 / op->dummy.buswidth > 64))
		return false;

	/* Max data length, check controller limits and alignment */
	if (op->data.dir == SPI_MEM_DATA_IN &&
	    (op->data.nbytes > q->devtype_data->ahb_buf_size ||
	     (op->data.nbytes > q->devtype_data->rxfifo - 4 &&
	      !IS_ALIGNED(op->data.nbytes, 8))))
		return false;

	if (op->data.dir == SPI_MEM_DATA_OUT &&
	    op->data.nbytes > q->devtype_data->txfifo)
		return false;

	return true;
}