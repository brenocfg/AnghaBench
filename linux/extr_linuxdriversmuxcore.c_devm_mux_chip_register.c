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
struct mux_chip {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_mux_chip_reg_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct mux_chip**) ; 
 struct mux_chip** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct mux_chip**) ; 
 int mux_chip_register (struct mux_chip*) ; 

int devm_mux_chip_register(struct device *dev,
			   struct mux_chip *mux_chip)
{
	struct mux_chip **ptr;
	int res;

	ptr = devres_alloc(devm_mux_chip_reg_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	res = mux_chip_register(mux_chip);
	if (res) {
		devres_free(ptr);
		return res;
	}

	*ptr = mux_chip;
	devres_add(dev, ptr);

	return res;
}