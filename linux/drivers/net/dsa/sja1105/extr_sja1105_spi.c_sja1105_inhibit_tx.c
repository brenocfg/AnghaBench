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
typedef  unsigned long u64 ;
struct sja1105_regs {int /*<<< orphan*/  port_control; } ;
struct sja1105_private {TYPE_1__* info; } ;
struct TYPE_2__ {struct sja1105_regs* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SJA1105_SIZE_PORT_CTRL ; 
 int /*<<< orphan*/  SPI_READ ; 
 int /*<<< orphan*/  SPI_WRITE ; 
 int sja1105_spi_send_int (struct sja1105_private const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 

int sja1105_inhibit_tx(const struct sja1105_private *priv,
		       unsigned long port_bitmap, bool tx_inhibited)
{
	const struct sja1105_regs *regs = priv->info->regs;
	u64 inhibit_cmd;
	int rc;

	rc = sja1105_spi_send_int(priv, SPI_READ, regs->port_control,
				  &inhibit_cmd, SJA1105_SIZE_PORT_CTRL);
	if (rc < 0)
		return rc;

	if (tx_inhibited)
		inhibit_cmd |= port_bitmap;
	else
		inhibit_cmd &= ~port_bitmap;

	return sja1105_spi_send_int(priv, SPI_WRITE, regs->port_control,
				    &inhibit_cmd, SJA1105_SIZE_PORT_CTRL);
}