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
struct stm32_qspi {int /*<<< orphan*/  lock; } ;
struct spi_mem_op {int dummy; } ;
struct spi_mem {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stm32_qspi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 int stm32_qspi_send (struct spi_mem*,struct spi_mem_op const*) ; 

__attribute__((used)) static int stm32_qspi_exec_op(struct spi_mem *mem, const struct spi_mem_op *op)
{
	struct stm32_qspi *qspi = spi_controller_get_devdata(mem->spi->master);
	int ret;

	mutex_lock(&qspi->lock);
	ret = stm32_qspi_send(mem, op);
	mutex_unlock(&qspi->lock);

	return ret;
}