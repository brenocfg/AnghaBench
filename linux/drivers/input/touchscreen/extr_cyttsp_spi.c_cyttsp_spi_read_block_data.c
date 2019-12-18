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
typedef  int /*<<< orphan*/  u16 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_SPI_RD_OP ; 
 int cyttsp_spi_xfer (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyttsp_spi_read_block_data(struct device *dev, u8 *xfer_buf,
				      u16 addr, u8 length, void *data)
{
	return cyttsp_spi_xfer(dev, xfer_buf, CY_SPI_RD_OP, addr, data,
			length);
}