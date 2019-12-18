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
typedef  int u8 ;
typedef  int u32 ;
struct mcp3911 {TYPE_1__* spi; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MCP3911_REG_READ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpus (int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int spi_write_then_read (TYPE_1__*,int*,int,int*,int) ; 

__attribute__((used)) static int mcp3911_read(struct mcp3911 *adc, u8 reg, u32 *val, u8 len)
{
	int ret;

	reg = MCP3911_REG_READ(reg, adc->dev_addr);
	ret = spi_write_then_read(adc->spi, &reg, 1, val, len);
	if (ret < 0)
		return ret;

	be32_to_cpus(val);
	*val >>= ((4 - len) * 8);
	dev_dbg(&adc->spi->dev, "reading 0x%x from register 0x%x\n", *val,
		reg >> 1);
	return ret;
}