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
struct TYPE_4__ {int /*<<< orphan*/  in; } ;
struct TYPE_6__ {int /*<<< orphan*/  nbytes; TYPE_1__ buf; } ;
struct spi_mem_op {TYPE_3__ data; } ;
struct fsl_qspi {int selected; TYPE_2__* devtype_data; scalar_t__ ahb_addr; } ;
struct TYPE_5__ {int ahb_buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_qspi_read_ahb(struct fsl_qspi *q, const struct spi_mem_op *op)
{
	memcpy_fromio(op->data.buf.in,
		      q->ahb_addr + q->selected * q->devtype_data->ahb_buf_size,
		      op->data.nbytes);
}