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
struct stmpe {TYPE_1__* variant; struct spi_device* client; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int id_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMPE811_REG_SPI_CFG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spi_reg_write (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spi_setup (struct spi_device*) ; 

__attribute__((used)) static void spi_init(struct stmpe *stmpe)
{
	struct spi_device *spi = stmpe->client;

	spi->bits_per_word = 8;

	/* This register is only present for stmpe811 */
	if (stmpe->variant->id_val == 0x0811)
		spi_reg_write(stmpe, STMPE811_REG_SPI_CFG, spi->mode);

	if (spi_setup(spi) < 0)
		dev_dbg(&spi->dev, "spi_setup failed\n");
}