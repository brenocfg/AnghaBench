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
 int /*<<< orphan*/  ENOMEM ; 
 struct mux_chip* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mux_chip*) ; 
 int /*<<< orphan*/  devm_mux_chip_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct mux_chip**) ; 
 struct mux_chip** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct mux_chip**) ; 
 struct mux_chip* mux_chip_alloc (struct device*,unsigned int,size_t) ; 

struct mux_chip *devm_mux_chip_alloc(struct device *dev,
				     unsigned int controllers,
				     size_t sizeof_priv)
{
	struct mux_chip **ptr, *mux_chip;

	ptr = devres_alloc(devm_mux_chip_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	mux_chip = mux_chip_alloc(dev, controllers, sizeof_priv);
	if (IS_ERR(mux_chip)) {
		devres_free(ptr);
		return mux_chip;
	}

	*ptr = mux_chip;
	devres_add(dev, ptr);

	return mux_chip;
}