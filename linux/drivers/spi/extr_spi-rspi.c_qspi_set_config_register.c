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
struct rspi_data {int sppcr; int max_speed_hz; int byte_access; int spcmd; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QSPI_SPBFCR ; 
 int /*<<< orphan*/  QSPI_SPBMUL0 ; 
 int /*<<< orphan*/  RSPI_SPBR ; 
 int /*<<< orphan*/  RSPI_SPCKD ; 
 int /*<<< orphan*/  RSPI_SPCMD0 ; 
 int /*<<< orphan*/  RSPI_SPCR ; 
 int /*<<< orphan*/  RSPI_SPDCR ; 
 int /*<<< orphan*/  RSPI_SPND ; 
 int /*<<< orphan*/  RSPI_SPPCR ; 
 int /*<<< orphan*/  RSPI_SPSCR ; 
 int /*<<< orphan*/  RSPI_SSLND ; 
 int SPBFCR_RXRST ; 
 int SPBFCR_TXRST ; 
 int SPCMD_SCKDEN ; 
 int SPCMD_SLNDEN ; 
 int SPCMD_SPB_16BIT ; 
 int SPCMD_SPB_32BIT ; 
 int SPCMD_SPB_8BIT ; 
 int SPCMD_SPNDEN ; 
 int SPCR_MSTR ; 
 int clamp (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write16 (struct rspi_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write32 (struct rspi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qspi_set_config_register(struct rspi_data *rspi, int access_size)
{
	int spbr;

	/* Sets output mode, MOSI signal, and (optionally) loopback */
	rspi_write8(rspi, rspi->sppcr, RSPI_SPPCR);

	/* Sets transfer bit rate */
	spbr = DIV_ROUND_UP(clk_get_rate(rspi->clk), 2 * rspi->max_speed_hz);
	rspi_write8(rspi, clamp(spbr, 0, 255), RSPI_SPBR);

	/* Disable dummy transmission, set byte access */
	rspi_write8(rspi, 0, RSPI_SPDCR);
	rspi->byte_access = 1;

	/* Sets RSPCK, SSL, next-access delay value */
	rspi_write8(rspi, 0x00, RSPI_SPCKD);
	rspi_write8(rspi, 0x00, RSPI_SSLND);
	rspi_write8(rspi, 0x00, RSPI_SPND);

	/* Data Length Setting */
	if (access_size == 8)
		rspi->spcmd |= SPCMD_SPB_8BIT;
	else if (access_size == 16)
		rspi->spcmd |= SPCMD_SPB_16BIT;
	else
		rspi->spcmd |= SPCMD_SPB_32BIT;

	rspi->spcmd |= SPCMD_SCKDEN | SPCMD_SLNDEN | SPCMD_SPNDEN;

	/* Resets transfer data length */
	rspi_write32(rspi, 0, QSPI_SPBMUL0);

	/* Resets transmit and receive buffer */
	rspi_write8(rspi, SPBFCR_TXRST | SPBFCR_RXRST, QSPI_SPBFCR);
	/* Sets buffer to allow normal operation */
	rspi_write8(rspi, 0x00, QSPI_SPBFCR);

	/* Resets sequencer */
	rspi_write8(rspi, 0, RSPI_SPSCR);
	rspi_write16(rspi, rspi->spcmd, RSPI_SPCMD0);

	/* Sets RSPI mode */
	rspi_write8(rspi, SPCR_MSTR, RSPI_SPCR);

	return 0;
}