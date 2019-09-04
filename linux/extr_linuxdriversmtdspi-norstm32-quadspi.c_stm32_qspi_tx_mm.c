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
struct stm32_qspi_cmd {int /*<<< orphan*/  len; scalar_t__ addr; int /*<<< orphan*/  buf; } ;
struct stm32_qspi {scalar_t__ mm_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_qspi_tx_mm(struct stm32_qspi *qspi,
			    const struct stm32_qspi_cmd *cmd)
{
	memcpy_fromio(cmd->buf, qspi->mm_base + cmd->addr, cmd->len);
	return 0;
}