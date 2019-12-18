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
struct TYPE_7__ {int buswidth; int nbytes; } ;
struct TYPE_8__ {int buswidth; scalar_t__ nbytes; } ;
struct TYPE_6__ {int buswidth; scalar_t__ nbytes; } ;
struct TYPE_5__ {int buswidth; } ;
struct spi_mem_op {TYPE_3__ addr; TYPE_4__ dummy; TYPE_2__ data; TYPE_1__ cmd; } ;
struct spi_mem {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool mxic_spi_mem_supports_op(struct spi_mem *mem,
				     const struct spi_mem_op *op)
{
	if (op->data.buswidth > 4 || op->addr.buswidth > 4 ||
	    op->dummy.buswidth > 4 || op->cmd.buswidth > 4)
		return false;

	if (op->data.nbytes && op->dummy.nbytes &&
	    op->data.buswidth != op->dummy.buswidth)
		return false;

	if (op->addr.nbytes > 7)
		return false;

	return true;
}