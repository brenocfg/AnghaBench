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
struct TYPE_6__ {scalar_t__ nbytes; } ;
struct TYPE_5__ {int nbytes; scalar_t__ buswidth; } ;
struct TYPE_4__ {scalar_t__ buswidth; } ;
struct spi_mem_op {TYPE_3__ dummy; TYPE_2__ addr; TYPE_1__ cmd; } ;
struct spi_mem {int dummy; } ;

/* Variables and functions */
 scalar_t__ atmel_qspi_find_mode (struct spi_mem_op const*) ; 

__attribute__((used)) static bool atmel_qspi_supports_op(struct spi_mem *mem,
				   const struct spi_mem_op *op)
{
	if (atmel_qspi_find_mode(op) < 0)
		return false;

	/* special case not supported by hardware */
	if (op->addr.nbytes == 2 && op->cmd.buswidth != op->addr.buswidth &&
		op->dummy.nbytes == 0)
		return false;

	return true;
}