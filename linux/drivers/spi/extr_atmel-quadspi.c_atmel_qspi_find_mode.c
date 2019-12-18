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
typedef  size_t u32 ;
struct spi_mem_op {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOTSUPP ; 
 scalar_t__ atmel_qspi_is_compatible (struct spi_mem_op const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * atmel_qspi_modes ; 

__attribute__((used)) static int atmel_qspi_find_mode(const struct spi_mem_op *op)
{
	u32 i;

	for (i = 0; i < ARRAY_SIZE(atmel_qspi_modes); i++)
		if (atmel_qspi_is_compatible(op, &atmel_qspi_modes[i]))
			return i;

	return -ENOTSUPP;
}