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
struct fsl_qspi {unsigned long clk_rate; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  fsl_qspi_clk_disable_unprep (struct fsl_qspi*) ; 
 int fsl_qspi_clk_prep_enable (struct fsl_qspi*) ; 
 int fsl_qspi_init_ahb_read (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_init_lut (struct fsl_qspi*) ; 
 scalar_t__ needs_4x_clock (struct fsl_qspi*) ; 

__attribute__((used)) static int fsl_qspi_nor_setup_last(struct fsl_qspi *q)
{
	unsigned long rate = q->clk_rate;
	int ret;

	if (needs_4x_clock(q))
		rate *= 4;

	/* disable and unprepare clock to avoid glitch pass to controller */
	fsl_qspi_clk_disable_unprep(q);

	ret = clk_set_rate(q->clk, rate);
	if (ret)
		return ret;

	ret = fsl_qspi_clk_prep_enable(q);
	if (ret)
		return ret;

	/* Init the LUT table again. */
	fsl_qspi_init_lut(q);

	/* Init for AHB read */
	return fsl_qspi_init_ahb_read(q);
}