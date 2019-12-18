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
typedef  int u32 ;
struct a3700_spi {TYPE_1__* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int A3700_SPI_ADDR_PIN ; 
 int A3700_SPI_DATA_PIN0 ; 
 int A3700_SPI_DATA_PIN1 ; 
 int /*<<< orphan*/  A3700_SPI_IF_CFG_REG ; 
 int A3700_SPI_INST_PIN ; 
 int EINVAL ; 
#define  SPI_NBITS_DUAL 130 
#define  SPI_NBITS_QUAD 129 
#define  SPI_NBITS_SINGLE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a3700_spi_pin_mode_set(struct a3700_spi *a3700_spi,
				  unsigned int pin_mode, bool receiving)
{
	u32 val;

	val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
	val &= ~(A3700_SPI_INST_PIN | A3700_SPI_ADDR_PIN);
	val &= ~(A3700_SPI_DATA_PIN0 | A3700_SPI_DATA_PIN1);

	switch (pin_mode) {
	case SPI_NBITS_SINGLE:
		break;
	case SPI_NBITS_DUAL:
		val |= A3700_SPI_DATA_PIN0;
		break;
	case SPI_NBITS_QUAD:
		val |= A3700_SPI_DATA_PIN1;
		/* RX during address reception uses 4-pin */
		if (receiving)
			val |= A3700_SPI_ADDR_PIN;
		break;
	default:
		dev_err(&a3700_spi->master->dev, "wrong pin mode %u", pin_mode);
		return -EINVAL;
	}

	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	return 0;
}