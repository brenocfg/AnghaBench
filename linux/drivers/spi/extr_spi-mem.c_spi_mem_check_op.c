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
struct TYPE_7__ {int /*<<< orphan*/  buswidth; scalar_t__ nbytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  buswidth; scalar_t__ nbytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  buswidth; scalar_t__ nbytes; } ;
struct TYPE_8__ {int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_3__ data; TYPE_2__ dummy; TYPE_1__ addr; TYPE_4__ cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spi_mem_buswidth_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_mem_check_op(const struct spi_mem_op *op)
{
	if (!op->cmd.buswidth)
		return -EINVAL;

	if ((op->addr.nbytes && !op->addr.buswidth) ||
	    (op->dummy.nbytes && !op->dummy.buswidth) ||
	    (op->data.nbytes && !op->data.buswidth))
		return -EINVAL;

	if (!spi_mem_buswidth_is_valid(op->cmd.buswidth) ||
	    !spi_mem_buswidth_is_valid(op->addr.buswidth) ||
	    !spi_mem_buswidth_is_valid(op->dummy.buswidth) ||
	    !spi_mem_buswidth_is_valid(op->data.buswidth))
		return -EINVAL;

	return 0;
}