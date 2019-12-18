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
struct spi_nor_hwcaps {int dummy; } ;
struct TYPE_2__ {int (* setup ) (struct spi_nor*,struct spi_nor_hwcaps const*) ;} ;
struct spi_nor {TYPE_1__ params; } ;

/* Variables and functions */
 int stub1 (struct spi_nor*,struct spi_nor_hwcaps const*) ; 

__attribute__((used)) static int spi_nor_setup(struct spi_nor *nor,
			 const struct spi_nor_hwcaps *hwcaps)
{
	if (!nor->params.setup)
		return 0;

	return nor->params.setup(nor, hwcaps);
}