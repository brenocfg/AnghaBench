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
struct nxp_fspi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct nxp_fspi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nxp_fspi_default_setup (struct nxp_fspi*) ; 

__attribute__((used)) static int nxp_fspi_resume(struct device *dev)
{
	struct nxp_fspi *f = dev_get_drvdata(dev);

	nxp_fspi_default_setup(f);

	return 0;
}