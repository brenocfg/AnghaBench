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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct fpga_data {int /*<<< orphan*/  fw_loaded; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FIRMWARE_NAME ; 
 int /*<<< orphan*/  FW_ACTION_HOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct fpga_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_load ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct fpga_data*) ; 

__attribute__((used)) static int lattice_ecp3_probe(struct spi_device *spi)
{
	struct fpga_data *data;
	int err;

	data = devm_kzalloc(&spi->dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		dev_err(&spi->dev, "Memory allocation for fpga_data failed\n");
		return -ENOMEM;
	}
	spi_set_drvdata(spi, data);

	init_completion(&data->fw_loaded);
	err = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
				      FIRMWARE_NAME, &spi->dev,
				      GFP_KERNEL, spi, firmware_load);
	if (err) {
		dev_err(&spi->dev, "Firmware loading failed with %d!\n", err);
		return err;
	}

	dev_info(&spi->dev, "FPGA bitstream configuration driver registered\n");

	return 0;
}