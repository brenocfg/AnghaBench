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
struct stm32_qspi_cmd {scalar_t__ qspimode; int /*<<< orphan*/  tx_data; } ;
struct stm32_qspi {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCR_FMODE_MM ; 
 int stm32_qspi_tx_mm (struct stm32_qspi*,struct stm32_qspi_cmd const*) ; 
 int stm32_qspi_tx_poll (struct stm32_qspi*,struct stm32_qspi_cmd const*) ; 

__attribute__((used)) static int stm32_qspi_tx(struct stm32_qspi *qspi,
			 const struct stm32_qspi_cmd *cmd)
{
	if (!cmd->tx_data)
		return 0;

	if (cmd->qspimode == CCR_FMODE_MM)
		return stm32_qspi_tx_mm(qspi, cmd);

	return stm32_qspi_tx_poll(qspi, cmd);
}