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
struct spi_transfer {int cs_change; int /*<<< orphan*/  delay_usecs; } ;
struct spi_message {int dummy; } ;
struct spi_device {int /*<<< orphan*/  master; int /*<<< orphan*/  dev; } ;
struct ice40_fpga_priv {int /*<<< orphan*/  cdone; int /*<<< orphan*/  reset; struct spi_device* dev; } ;
struct fpga_manager {struct ice40_fpga_priv* priv; } ;
struct fpga_image_info {int flags; } ;

/* Variables and functions */
 int EIO ; 
 int ENOTSUPP ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  ICE40_SPI_HOUSEKEEPING_DELAY ; 
 int /*<<< orphan*/  ICE40_SPI_RESET_DELAY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync_locked (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int ice40_fpga_ops_write_init(struct fpga_manager *mgr,
				     struct fpga_image_info *info,
				     const char *buf, size_t count)
{
	struct ice40_fpga_priv *priv = mgr->priv;
	struct spi_device *dev = priv->dev;
	struct spi_message message;
	struct spi_transfer assert_cs_then_reset_delay = {
		.cs_change   = 1,
		.delay_usecs = ICE40_SPI_RESET_DELAY
	};
	struct spi_transfer housekeeping_delay_then_release_cs = {
		.delay_usecs = ICE40_SPI_HOUSEKEEPING_DELAY
	};
	int ret;

	if ((info->flags & FPGA_MGR_PARTIAL_RECONFIG)) {
		dev_err(&dev->dev,
			"Partial reconfiguration is not supported\n");
		return -ENOTSUPP;
	}

	/* Lock the bus, assert CRESET_B and SS_B and delay >200ns */
	spi_bus_lock(dev->master);

	gpiod_set_value(priv->reset, 1);

	spi_message_init(&message);
	spi_message_add_tail(&assert_cs_then_reset_delay, &message);
	ret = spi_sync_locked(dev, &message);

	/* Come out of reset */
	gpiod_set_value(priv->reset, 0);

	/* Abort if the chip-select failed */
	if (ret)
		goto fail;

	/* Check CDONE is de-asserted i.e. the FPGA is reset */
	if (gpiod_get_value(priv->cdone)) {
		dev_err(&dev->dev, "Device reset failed, CDONE is asserted\n");
		ret = -EIO;
		goto fail;
	}

	/* Wait for the housekeeping to complete, and release SS_B */
	spi_message_init(&message);
	spi_message_add_tail(&housekeeping_delay_then_release_cs, &message);
	ret = spi_sync_locked(dev, &message);

fail:
	spi_bus_unlock(dev->master);

	return ret;
}