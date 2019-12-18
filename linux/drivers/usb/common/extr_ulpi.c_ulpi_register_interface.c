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
struct ulpi_ops {int dummy; } ;
struct ulpi {struct ulpi_ops const* ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ulpi* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ulpi*) ; 
 struct ulpi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ulpi_register (struct device*,struct ulpi*) ; 

struct ulpi *ulpi_register_interface(struct device *dev,
				     const struct ulpi_ops *ops)
{
	struct ulpi *ulpi;
	int ret;

	ulpi = kzalloc(sizeof(*ulpi), GFP_KERNEL);
	if (!ulpi)
		return ERR_PTR(-ENOMEM);

	ulpi->ops = ops;

	ret = ulpi_register(dev, ulpi);
	if (ret) {
		kfree(ulpi);
		return ERR_PTR(ret);
	}

	return ulpi;
}