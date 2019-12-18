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
typedef  int /*<<< orphan*/  u16 ;
struct fsl_dspi {scalar_t__ len; int /*<<< orphan*/  regmap_pushr; int /*<<< orphan*/  tx_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHR_CMD ; 
 int /*<<< orphan*/  SPI_PUSHR_CMD_CONT ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_fifo_write(struct fsl_dspi *dspi)
{
	u16 cmd = dspi->tx_cmd;

	if (dspi->len > 0)
		cmd |= SPI_PUSHR_CMD_CONT;
	regmap_write(dspi->regmap_pushr, PUSHR_CMD, cmd);
}