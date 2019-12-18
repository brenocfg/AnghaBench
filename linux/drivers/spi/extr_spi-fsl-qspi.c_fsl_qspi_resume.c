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
struct fsl_qspi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct fsl_qspi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fsl_qspi_default_setup (struct fsl_qspi*) ; 

__attribute__((used)) static int fsl_qspi_resume(struct device *dev)
{
	struct fsl_qspi *q = dev_get_drvdata(dev);

	fsl_qspi_default_setup(q);

	return 0;
}