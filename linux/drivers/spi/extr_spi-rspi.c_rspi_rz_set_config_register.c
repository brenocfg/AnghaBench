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
struct rspi_data {int sppcr; unsigned long max_speed_hz; int spcmd; int byte_access; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  RSPI_SPBR ; 
 int /*<<< orphan*/  RSPI_SPCKD ; 
 int /*<<< orphan*/  RSPI_SPCMD0 ; 
 int /*<<< orphan*/  RSPI_SPCR ; 
 int /*<<< orphan*/  RSPI_SPDCR ; 
 int /*<<< orphan*/  RSPI_SPND ; 
 int /*<<< orphan*/  RSPI_SPPCR ; 
 int /*<<< orphan*/  RSPI_SPSCR ; 
 int /*<<< orphan*/  RSPI_SSLND ; 
 int SPCMD_SPB_8_TO_16 (int) ; 
 int SPCR_MSTR ; 
 int SPDCR_SPLBYTE ; 
 int clamp (int,int /*<<< orphan*/ ,int) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write16 (struct rspi_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rspi_rz_set_config_register(struct rspi_data *rspi, int access_size)
{
	int spbr;
	int div = 0;
	unsigned long clksrc;

	/* Sets output mode, MOSI signal, and (optionally) loopback */
	rspi_write8(rspi, rspi->sppcr, RSPI_SPPCR);

	clksrc = clk_get_rate(rspi->clk);
	while (div < 3) {
		if (rspi->max_speed_hz >= clksrc/4) /* 4=(CLK/2)/2 */
			break;
		div++;
		clksrc /= 2;
	}

	/* Sets transfer bit rate */
	spbr = DIV_ROUND_UP(clksrc, 2 * rspi->max_speed_hz) - 1;
	rspi_write8(rspi, clamp(spbr, 0, 255), RSPI_SPBR);
	rspi->spcmd |= div << 2;

	/* Disable dummy transmission, set byte access */
	rspi_write8(rspi, SPDCR_SPLBYTE, RSPI_SPDCR);
	rspi->byte_access = 1;

	/* Sets RSPCK, SSL, next-access delay value */
	rspi_write8(rspi, 0x00, RSPI_SPCKD);
	rspi_write8(rspi, 0x00, RSPI_SSLND);
	rspi_write8(rspi, 0x00, RSPI_SPND);

	/* Resets sequencer */
	rspi_write8(rspi, 0, RSPI_SPSCR);
	rspi->spcmd |= SPCMD_SPB_8_TO_16(access_size);
	rspi_write16(rspi, rspi->spcmd, RSPI_SPCMD0);

	/* Sets RSPI mode */
	rspi_write8(rspi, SPCR_MSTR, RSPI_SPCR);

	return 0;
}