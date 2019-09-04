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
typedef  int u32 ;
struct stm32_qspi {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ QUADSPI_SR ; 
 int SR_BUSY ; 
 int /*<<< orphan*/  STM32_QSPI_BUSY_TIMEOUT_US ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_qspi_wait_nobusy(struct stm32_qspi *qspi)
{
	u32 sr;

	return readl_relaxed_poll_timeout(qspi->io_base + QUADSPI_SR, sr,
					  !(sr & SR_BUSY), 10,
					  STM32_QSPI_BUSY_TIMEOUT_US);
}