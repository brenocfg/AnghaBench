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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tx_buf ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int spi_write_then_read (struct spi_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adgs1408_spi_reg_write(struct spi_device *spi,
				  u8 reg_addr, u8 reg_data)
{
	u8 tx_buf[2];

	tx_buf[0] = reg_addr;
	tx_buf[1] = reg_data;

	return spi_write_then_read(spi, tx_buf, sizeof(tx_buf), NULL, 0);
}