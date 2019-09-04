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
struct ts73xx_fpga_priv {scalar_t__ io_base; } ;
struct fpga_manager {struct ts73xx_fpga_priv* priv; } ;
struct fpga_image_info {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int TS73XX_FPGA_CONFIG_LOAD ; 
 scalar_t__ TS73XX_FPGA_CONFIG_REG ; 
 int TS73XX_FPGA_LOAD_OK ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int ts73xx_fpga_write_complete(struct fpga_manager *mgr,
				      struct fpga_image_info *info)
{
	struct ts73xx_fpga_priv *priv = mgr->priv;
	u8 reg;

	usleep_range(1000, 2000);
	reg = readb(priv->io_base + TS73XX_FPGA_CONFIG_REG);
	reg |= TS73XX_FPGA_CONFIG_LOAD;
	writeb(reg, priv->io_base + TS73XX_FPGA_CONFIG_REG);

	usleep_range(1000, 2000);
	reg = readb(priv->io_base + TS73XX_FPGA_CONFIG_REG);
	reg &= ~TS73XX_FPGA_CONFIG_LOAD;
	writeb(reg, priv->io_base + TS73XX_FPGA_CONFIG_REG);

	reg = readb(priv->io_base + TS73XX_FPGA_CONFIG_REG);
	if ((reg & TS73XX_FPGA_LOAD_OK) != TS73XX_FPGA_LOAD_OK)
		return -ETIMEDOUT;

	return 0;
}