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
struct TYPE_6__ {scalar_t__ buswidth; scalar_t__ nbytes; } ;
struct TYPE_5__ {scalar_t__ buswidth; scalar_t__ nbytes; } ;
struct TYPE_4__ {scalar_t__ buswidth; } ;
struct spi_mem_op {TYPE_3__ data; TYPE_2__ addr; TYPE_1__ cmd; } ;
struct atmel_qspi_mode {scalar_t__ cmd_buswidth; scalar_t__ addr_buswidth; scalar_t__ data_buswidth; } ;

/* Variables and functions */

__attribute__((used)) static inline bool atmel_qspi_is_compatible(const struct spi_mem_op *op,
					    const struct atmel_qspi_mode *mode)
{
	if (op->cmd.buswidth != mode->cmd_buswidth)
		return false;

	if (op->addr.nbytes && op->addr.buswidth != mode->addr_buswidth)
		return false;

	if (op->data.nbytes && op->data.buswidth != mode->data_buswidth)
		return false;

	return true;
}