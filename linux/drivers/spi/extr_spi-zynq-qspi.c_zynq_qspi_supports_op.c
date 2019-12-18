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
struct TYPE_2__ {int nbytes; } ;
struct spi_mem_op {TYPE_1__ addr; } ;
struct spi_mem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_mem_default_supports_op (struct spi_mem*,struct spi_mem_op const*) ; 

__attribute__((used)) static bool zynq_qspi_supports_op(struct spi_mem *mem,
				  const struct spi_mem_op *op)
{
	if (!spi_mem_default_supports_op(mem, op))
		return false;

	/*
	 * The number of address bytes should be equal to or less than 3 bytes.
	 */
	if (op->addr.nbytes > 3)
		return false;

	return true;
}