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
 int /*<<< orphan*/  spi_mem_dirmap_destroy (struct spi_mem_dirmap_desc*) ; 

__attribute__((used)) static void devm_spi_mem_dirmap_release(struct device *dev, void *res)
{
	struct spi_mem_dirmap_desc *desc = *(struct spi_mem_dirmap_desc **)res;

	spi_mem_dirmap_destroy(desc);
}