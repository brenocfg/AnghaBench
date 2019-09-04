#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct resource {scalar_t__ start; int /*<<< orphan*/  end; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * reglen; scalar_t__** regs; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int BIT (int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  devm_request_region (struct device*,scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__ ichx_priv ; 

__attribute__((used)) static int ichx_gpio_request_regions(struct device *dev,
	struct resource *res_base, const char *name, u8 use_gpio)
{
	int i;

	if (!res_base || !res_base->start || !res_base->end)
		return -ENODEV;

	for (i = 0; i < ARRAY_SIZE(ichx_priv.desc->regs[0]); i++) {
		if (!(use_gpio & BIT(i)))
			continue;
		if (!devm_request_region(dev,
				res_base->start + ichx_priv.desc->regs[0][i],
				ichx_priv.desc->reglen[i], name))
			return -EBUSY;
	}
	return 0;
}