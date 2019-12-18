#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sja1105_reset_cmd {scalar_t__ por_rst; scalar_t__ cold_rst; scalar_t__ warm_rst; scalar_t__ otp_rst; scalar_t__ car_rst; scalar_t__ cfg_rst; scalar_t__ switch_rst; } ;
struct sja1105_regs {int /*<<< orphan*/  rgu; } ;
struct sja1105_private {TYPE_2__* ds; TYPE_1__* info; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;
struct TYPE_3__ {struct sja1105_regs* regs; } ;

/* Variables and functions */
 int SJA1105_SIZE_RESET_CMD ; 
 int /*<<< orphan*/  SPI_WRITE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int sja1105_spi_send_packed_buf (struct sja1105_private const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sja1105pqrs_reset_cmd_pack (int /*<<< orphan*/ *,struct sja1105_reset_cmd const*) ; 

__attribute__((used)) static int sja1105pqrs_reset_cmd(const void *ctx, const void *data)
{
	const struct sja1105_private *priv = ctx;
	const struct sja1105_reset_cmd *reset = data;
	const struct sja1105_regs *regs = priv->info->regs;
	struct device *dev = priv->ds->dev;
	u8 packed_buf[SJA1105_SIZE_RESET_CMD];

	if (reset->switch_rst)
		dev_dbg(dev, "Main reset for all functional modules requested\n");
	if (reset->cfg_rst)
		dev_dbg(dev, "Chip configuration reset requested\n");
	if (reset->car_rst)
		dev_dbg(dev, "Clock and reset control logic reset requested\n");
	if (reset->otp_rst)
		dev_dbg(dev, "OTP read cycle for reading product "
			"config settings requested\n");
	if (reset->warm_rst)
		dev_dbg(dev, "Warm reset requested\n");
	if (reset->cold_rst)
		dev_dbg(dev, "Cold reset requested\n");
	if (reset->por_rst)
		dev_dbg(dev, "Power-on reset requested\n");

	sja1105pqrs_reset_cmd_pack(packed_buf, reset);

	return sja1105_spi_send_packed_buf(priv, SPI_WRITE, regs->rgu,
					   packed_buf, SJA1105_SIZE_RESET_CMD);
}