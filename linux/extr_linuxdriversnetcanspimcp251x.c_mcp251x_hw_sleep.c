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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANCTRL ; 
 int /*<<< orphan*/  CANCTRL_REQOP_SLEEP ; 
 int /*<<< orphan*/  mcp251x_write_reg (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcp251x_hw_sleep(struct spi_device *spi)
{
	mcp251x_write_reg(spi, CANCTRL, CANCTRL_REQOP_SLEEP);
}