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
struct stm32_qspi {scalar_t__ mm_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  in; } ;
struct TYPE_6__ {int /*<<< orphan*/  nbytes; TYPE_1__ buf; } ;
struct TYPE_5__ {scalar_t__ val; } ;
struct spi_mem_op {TYPE_3__ data; TYPE_2__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_qspi_tx_mm(struct stm32_qspi *qspi,
			    const struct spi_mem_op *op)
{
	memcpy_fromio(op->data.buf.in, qspi->mm_base + op->addr.val,
		      op->data.nbytes);
	return 0;
}