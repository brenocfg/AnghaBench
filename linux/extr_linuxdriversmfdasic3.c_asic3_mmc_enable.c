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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct asic3 {scalar_t__ bus_shift; int /*<<< orphan*/  tmio_cnf; int /*<<< orphan*/ * clocks; } ;

/* Variables and functions */
 size_t ASIC3_CLOCK_EX0 ; 
 size_t ASIC3_CLOCK_EX1 ; 
 size_t ASIC3_CLOCK_SD_BUS ; 
 size_t ASIC3_CLOCK_SD_HOST ; 
 int /*<<< orphan*/  ASIC3_EXTCF_SD_MEM_ENABLE ; 
 int /*<<< orphan*/  ASIC3_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC3_SDHWCTRL_LEVCD ; 
 int /*<<< orphan*/  ASIC3_SDHWCTRL_LEVWP ; 
 int /*<<< orphan*/  ASIC3_SDHWCTRL_PCLR ; 
 int /*<<< orphan*/  ASIC3_SDHWCTRL_SDPWR ; 
 int /*<<< orphan*/  ASIC3_SDHWCTRL_SUSPEND ; 
 int ASIC3_SD_CTRL_BASE ; 
 int /*<<< orphan*/  CLOCK ; 
 int CLOCK_SEL_CX ; 
 int CLOCK_SEL_SD_HCLK_SEL ; 
 int /*<<< orphan*/  EXTCF ; 
 int /*<<< orphan*/  SDCONF ; 
 int /*<<< orphan*/  SDHWCTRL ; 
 int /*<<< orphan*/  SEL ; 
 int /*<<< orphan*/  SELECT ; 
 int /*<<< orphan*/  asic3_clk_enable (struct asic3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asic3_set_register (struct asic3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asic3_write_register (struct asic3*,int /*<<< orphan*/ ,int) ; 
 struct asic3* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_core_mmc_enable (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int asic3_mmc_enable(struct platform_device *pdev)
{
	struct asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	/* Not sure if it must be done bit by bit, but leaving as-is */
	asic3_set_register(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_LEVCD, 1);
	asic3_set_register(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_LEVWP, 1);
	asic3_set_register(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_SUSPEND, 0);
	asic3_set_register(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_PCLR, 0);

	asic3_clk_enable(asic, &asic->clocks[ASIC3_CLOCK_EX0]);
	/* CLK32 used for card detection and for interruption detection
	 * when HCLK is stopped.
	 */
	asic3_clk_enable(asic, &asic->clocks[ASIC3_CLOCK_EX1]);
	usleep_range(1000, 5000);

	/* HCLK 24.576 MHz, BCLK 12.288 MHz: */
	asic3_write_register(asic, ASIC3_OFFSET(CLOCK, SEL),
		CLOCK_SEL_CX | CLOCK_SEL_SD_HCLK_SEL);

	asic3_clk_enable(asic, &asic->clocks[ASIC3_CLOCK_SD_HOST]);
	asic3_clk_enable(asic, &asic->clocks[ASIC3_CLOCK_SD_BUS]);
	usleep_range(1000, 5000);

	asic3_set_register(asic, ASIC3_OFFSET(EXTCF, SELECT),
			   ASIC3_EXTCF_SD_MEM_ENABLE, 1);

	/* Enable SD card slot 3.3V power supply */
	asic3_set_register(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_SDPWR, 1);

	/* ASIC3_SD_CTRL_BASE assumes 32-bit addressing, TMIO is 16-bit */
	tmio_core_mmc_enable(asic->tmio_cnf, 1 - asic->bus_shift,
			     ASIC3_SD_CTRL_BASE >> 1);

	return 0;
}