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
struct lpi2c_imx_struct {scalar_t__ base; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int GEN_START ; 
 scalar_t__ LPI2C_MCR ; 
 scalar_t__ LPI2C_MSR ; 
 scalar_t__ LPI2C_MTDR ; 
 unsigned int MCR_RRF ; 
 unsigned int MCR_RTF ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int lpi2c_imx_bus_busy (struct lpi2c_imx_struct*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int lpi2c_imx_start(struct lpi2c_imx_struct *lpi2c_imx,
			   struct i2c_msg *msgs)
{
	unsigned int temp;

	temp = readl(lpi2c_imx->base + LPI2C_MCR);
	temp |= MCR_RRF | MCR_RTF;
	writel(temp, lpi2c_imx->base + LPI2C_MCR);
	writel(0x7f00, lpi2c_imx->base + LPI2C_MSR);

	temp = i2c_8bit_addr_from_msg(msgs) | (GEN_START << 8);
	writel(temp, lpi2c_imx->base + LPI2C_MTDR);

	return lpi2c_imx_bus_busy(lpi2c_imx);
}