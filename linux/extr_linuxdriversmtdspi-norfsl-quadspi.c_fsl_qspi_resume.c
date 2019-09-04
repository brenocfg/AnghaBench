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
struct platform_device {int dummy; } ;
struct fsl_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_qspi_clk_disable_unprep (struct fsl_qspi*) ; 
 int fsl_qspi_clk_prep_enable (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_nor_setup (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_nor_setup_last (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_set_map_addr (struct fsl_qspi*) ; 
 struct fsl_qspi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fsl_qspi_resume(struct platform_device *pdev)
{
	int ret;
	struct fsl_qspi *q = platform_get_drvdata(pdev);

	ret = fsl_qspi_clk_prep_enable(q);
	if (ret)
		return ret;

	fsl_qspi_nor_setup(q);
	fsl_qspi_set_map_addr(q);
	fsl_qspi_nor_setup_last(q);

	fsl_qspi_clk_disable_unprep(q);

	return 0;
}