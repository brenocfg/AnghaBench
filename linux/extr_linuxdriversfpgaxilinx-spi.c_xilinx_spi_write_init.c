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
struct xilinx_spi_conf {int /*<<< orphan*/  done; int /*<<< orphan*/  prog_b; } ;
struct fpga_manager {int /*<<< orphan*/  dev; struct xilinx_spi_conf* priv; } ;
struct fpga_image_info {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (size_t const) ; 
 int /*<<< orphan*/  usleep_range (size_t const,size_t const) ; 

__attribute__((used)) static int xilinx_spi_write_init(struct fpga_manager *mgr,
				 struct fpga_image_info *info,
				 const char *buf, size_t count)
{
	struct xilinx_spi_conf *conf = mgr->priv;
	const size_t prog_latency_7500us = 7500;
	const size_t prog_pulse_1us = 1;

	if (info->flags & FPGA_MGR_PARTIAL_RECONFIG) {
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		return -EINVAL;
	}

	gpiod_set_value(conf->prog_b, 1);

	udelay(prog_pulse_1us); /* min is 500 ns */

	gpiod_set_value(conf->prog_b, 0);

	if (gpiod_get_value(conf->done)) {
		dev_err(&mgr->dev, "Unexpected DONE pin state...\n");
		return -EIO;
	}

	/* program latency */
	usleep_range(prog_latency_7500us, prog_latency_7500us + 100);
	return 0;
}