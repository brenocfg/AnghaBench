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
struct spi_mem_dirmap_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_spi_mem_dirmap_match ; 
 int /*<<< orphan*/  devm_spi_mem_dirmap_release ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_mem_dirmap_desc*) ; 

void devm_spi_mem_dirmap_destroy(struct device *dev,
				 struct spi_mem_dirmap_desc *desc)
{
	devres_release(dev, devm_spi_mem_dirmap_release,
		       devm_spi_mem_dirmap_match, desc);
}