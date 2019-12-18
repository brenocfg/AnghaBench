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
struct TYPE_6__ {scalar_t__ dir; scalar_t__ nbytes; } ;
struct spi_mem_op {TYPE_3__ data; } ;
struct spi_mem {TYPE_1__* spi; } ;
struct nxp_fspi {TYPE_2__* devtype_data; } ;
struct TYPE_5__ {scalar_t__ txfifo; scalar_t__ ahb_buf_size; int rxfifo; } ;
struct TYPE_4__ {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int ALIGN_DOWN (int,int) ; 
 scalar_t__ SPI_MEM_DATA_OUT ; 
 struct nxp_fspi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxp_fspi_adjust_op_size(struct spi_mem *mem, struct spi_mem_op *op)
{
	struct nxp_fspi *f = spi_controller_get_devdata(mem->spi->master);

	if (op->data.dir == SPI_MEM_DATA_OUT) {
		if (op->data.nbytes > f->devtype_data->txfifo)
			op->data.nbytes = f->devtype_data->txfifo;
	} else {
		if (op->data.nbytes > f->devtype_data->ahb_buf_size)
			op->data.nbytes = f->devtype_data->ahb_buf_size;
		else if (op->data.nbytes > (f->devtype_data->rxfifo - 4))
			op->data.nbytes = ALIGN_DOWN(op->data.nbytes, 8);
	}

	return 0;
}