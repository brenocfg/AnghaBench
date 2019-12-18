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
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum mantisse { ____Placeholder_mantisse } mantisse ;

/* Variables and functions */
 int BW_MANT_16 ; 
 int BW_MANT_20 ; 
 int BW_MANT_24 ; 
 int EINVAL ; 
 int MASK_BW_DCC_FREQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
#define  mantisse16 130 
#define  mantisse20 129 
#define  mantisse24 128 
 int rf69_read_reg (struct spi_device*,int) ; 
 int rf69_write_reg (struct spi_device*,int,int) ; 

__attribute__((used)) static int rf69_set_bandwidth_intern(struct spi_device *spi, u8 reg,
				     enum mantisse mantisse, u8 exponent)
{
	u8 bandwidth;

	// check value for mantisse and exponent
	if (exponent > 7) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	if ((mantisse != mantisse16) &&
	    (mantisse != mantisse20) &&
	    (mantisse != mantisse24)) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	// read old value
	bandwidth = rf69_read_reg(spi, reg);

	// "delete" mantisse and exponent = just keep the DCC setting
	bandwidth = bandwidth & MASK_BW_DCC_FREQ;

	// add new mantisse
	switch (mantisse) {
	case mantisse16:
		bandwidth = bandwidth | BW_MANT_16;
		break;
	case mantisse20:
		bandwidth = bandwidth | BW_MANT_20;
		break;
	case mantisse24:
		bandwidth = bandwidth | BW_MANT_24;
		break;
	}

	// add new exponent
	bandwidth = bandwidth | exponent;

	// write back
	return rf69_write_reg(spi, reg, bandwidth);
}