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
typedef  int /*<<< orphan*/  tx ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCP795_READ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spi_write_then_read (struct spi_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int mcp795_rtcc_read(struct device *dev, u8 addr, u8 *buf, u8 count)
{
	struct spi_device *spi = to_spi_device(dev);
	int ret;
	u8 tx[2];

	tx[0] = MCP795_READ;
	tx[1] = addr;
	ret = spi_write_then_read(spi, tx, sizeof(tx), buf, count);

	if (ret)
		dev_err(dev, "Failed reading %d bytes from address %x.\n",
					count, addr);

	return ret;
}