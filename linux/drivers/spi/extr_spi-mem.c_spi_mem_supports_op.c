#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct spi_mem_op {int dummy; } ;
struct spi_mem {int dummy; } ;

/* Variables and functions */
 scalar_t__ spi_mem_check_op (struct spi_mem_op const*) ; 
 int spi_mem_internal_supports_op (struct spi_mem*,struct spi_mem_op const*) ; 

bool spi_mem_supports_op(struct spi_mem *mem, const struct spi_mem_op *op)
{
	if (spi_mem_check_op(op))
		return false;

	return spi_mem_internal_supports_op(mem, op);
}