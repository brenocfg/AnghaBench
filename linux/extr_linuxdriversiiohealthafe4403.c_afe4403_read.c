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
typedef  int u32 ;
struct afe4403_data {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int AFE440X_CONTROL0 ; 
 int AFE440X_CONTROL0_READ ; 
 int AFE440X_CONTROL0_WRITE ; 
 int spi_write_then_read (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int afe4403_read(struct afe4403_data *afe, unsigned int reg, u32 *val)
{
	u8 tx[4] = {AFE440X_CONTROL0, 0x0, 0x0, AFE440X_CONTROL0_READ};
	u8 rx[3];
	int ret;

	/* Enable reading from the device */
	ret = spi_write_then_read(afe->spi, tx, 4, NULL, 0);
	if (ret)
		return ret;

	ret = spi_write_then_read(afe->spi, &reg, 1, rx, 3);
	if (ret)
		return ret;

	*val = (rx[0] << 16) |
		(rx[1] << 8) |
		(rx[2]);

	/* Disable reading from the device */
	tx[3] = AFE440X_CONTROL0_WRITE;
	ret = spi_write_then_read(afe->spi, tx, 4, NULL, 0);
	if (ret)
		return ret;

	return 0;
}