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
struct spi_controller {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_spi_unregister ; 
 int /*<<< orphan*/  devres_add (struct device*,struct spi_controller**) ; 
 struct spi_controller** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct spi_controller**) ; 
 int spi_register_controller (struct spi_controller*) ; 

int devm_spi_register_controller(struct device *dev,
				 struct spi_controller *ctlr)
{
	struct spi_controller **ptr;
	int ret;

	ptr = devres_alloc(devm_spi_unregister, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = spi_register_controller(ctlr);
	if (!ret) {
		*ptr = ctlr;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return ret;
}