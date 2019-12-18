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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct zynqmp_qspi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GQSPI_GENFIFO_MODE_DUALSPI ; 
 int /*<<< orphan*/  GQSPI_GENFIFO_MODE_QUADSPI ; 
 int /*<<< orphan*/  GQSPI_GENFIFO_MODE_SPI ; 
#define  GQSPI_SELECT_MODE_DUALSPI 130 
#define  GQSPI_SELECT_MODE_QUADSPI 129 
#define  GQSPI_SELECT_MODE_SPI 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline u32 zynqmp_qspi_selectspimode(struct zynqmp_qspi *xqspi,
						u8 spimode)
{
	u32 mask = 0;

	switch (spimode) {
	case GQSPI_SELECT_MODE_DUALSPI:
		mask = GQSPI_GENFIFO_MODE_DUALSPI;
		break;
	case GQSPI_SELECT_MODE_QUADSPI:
		mask = GQSPI_GENFIFO_MODE_QUADSPI;
		break;
	case GQSPI_SELECT_MODE_SPI:
		mask = GQSPI_GENFIFO_MODE_SPI;
		break;
	default:
		dev_warn(xqspi->dev, "Invalid SPI mode\n");
	}

	return mask;
}