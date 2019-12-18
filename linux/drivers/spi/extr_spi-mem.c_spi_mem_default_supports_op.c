#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dir; int /*<<< orphan*/  buswidth; } ;
struct TYPE_8__ {int /*<<< orphan*/  buswidth; scalar_t__ nbytes; } ;
struct TYPE_7__ {int /*<<< orphan*/  buswidth; scalar_t__ nbytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_1__ data; TYPE_4__ dummy; TYPE_3__ addr; TYPE_2__ cmd; } ;
struct spi_mem {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPI_MEM_DATA_OUT ; 
 scalar_t__ SPI_MEM_NO_DATA ; 
 scalar_t__ spi_check_buswidth_req (struct spi_mem*,int /*<<< orphan*/ ,int) ; 

bool spi_mem_default_supports_op(struct spi_mem *mem,
				 const struct spi_mem_op *op)
{
	if (spi_check_buswidth_req(mem, op->cmd.buswidth, true))
		return false;

	if (op->addr.nbytes &&
	    spi_check_buswidth_req(mem, op->addr.buswidth, true))
		return false;

	if (op->dummy.nbytes &&
	    spi_check_buswidth_req(mem, op->dummy.buswidth, true))
		return false;

	if (op->data.dir != SPI_MEM_NO_DATA &&
	    spi_check_buswidth_req(mem, op->data.buswidth,
				   op->data.dir == SPI_MEM_DATA_OUT))
		return false;

	return true;
}