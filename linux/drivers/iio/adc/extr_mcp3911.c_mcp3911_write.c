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
 int MCP3911_REG_WRITE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32s (int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int spi_write (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int mcp3911_write(struct mcp3911 *adc, u8 reg, u32 val, u8 len)
{
	dev_dbg(&adc->spi->dev, "writing 0x%x to register 0x%x\n", val, reg);

	val <<= (3 - len) * 8;
	cpu_to_be32s(&val);
	val |= MCP3911_REG_WRITE(reg, adc->dev_addr);

	return spi_write(adc->spi, &val, len + 1);
}