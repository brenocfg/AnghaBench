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
struct bcm_qspi_parms {int bits_per_word; int /*<<< orphan*/  speed_hz; int /*<<< orphan*/  mode; } ;
struct bcm_qspi {int /*<<< orphan*/  max_speed_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSPI ; 
 int /*<<< orphan*/  MSPI_ENDQP ; 
 int /*<<< orphan*/  MSPI_NEWQP ; 
 int /*<<< orphan*/  MSPI_SPCR1_LSB ; 
 int /*<<< orphan*/  MSPI_SPCR1_MSB ; 
 int /*<<< orphan*/  MSPI_SPCR2 ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  bcm_qspi_bspi_init (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_hw_set_parms (struct bcm_qspi*,struct bcm_qspi_parms*) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ has_bspi (struct bcm_qspi*) ; 

__attribute__((used)) static void bcm_qspi_hw_init(struct bcm_qspi *qspi)
{
	struct bcm_qspi_parms parms;

	bcm_qspi_write(qspi, MSPI, MSPI_SPCR1_LSB, 0);
	bcm_qspi_write(qspi, MSPI, MSPI_SPCR1_MSB, 0);
	bcm_qspi_write(qspi, MSPI, MSPI_NEWQP, 0);
	bcm_qspi_write(qspi, MSPI, MSPI_ENDQP, 0);
	bcm_qspi_write(qspi, MSPI, MSPI_SPCR2, 0x20);

	parms.mode = SPI_MODE_3;
	parms.bits_per_word = 8;
	parms.speed_hz = qspi->max_speed_hz;
	bcm_qspi_hw_set_parms(qspi, &parms);

	if (has_bspi(qspi))
		bcm_qspi_bspi_init(qspi);
}