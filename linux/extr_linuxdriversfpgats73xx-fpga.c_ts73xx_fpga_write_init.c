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
struct ts73xx_fpga_priv {scalar_t__ io_base; } ;
struct fpga_manager {struct ts73xx_fpga_priv* priv; } ;
struct fpga_image_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ TS73XX_FPGA_CONFIG_REG ; 
 int /*<<< orphan*/  TS73XX_FPGA_RESET ; 
 int /*<<< orphan*/  TS73XX_FPGA_RESET_HIGH_DELAY ; 
 int /*<<< orphan*/  TS73XX_FPGA_RESET_LOW_DELAY ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ts73xx_fpga_write_init(struct fpga_manager *mgr,
				  struct fpga_image_info *info,
				  const char *buf, size_t count)
{
	struct ts73xx_fpga_priv *priv = mgr->priv;

	/* Reset the FPGA */
	writeb(0, priv->io_base + TS73XX_FPGA_CONFIG_REG);
	udelay(TS73XX_FPGA_RESET_LOW_DELAY);
	writeb(TS73XX_FPGA_RESET, priv->io_base + TS73XX_FPGA_CONFIG_REG);
	udelay(TS73XX_FPGA_RESET_HIGH_DELAY);

	return 0;
}