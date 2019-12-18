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
struct isc_device {TYPE_1__* isc_clks; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int isc_clk_register (struct isc_device*,unsigned int) ; 

int isc_clk_init(struct isc_device *isc)
{
	unsigned int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(isc->isc_clks); i++)
		isc->isc_clks[i].clk = ERR_PTR(-EINVAL);

	for (i = 0; i < ARRAY_SIZE(isc->isc_clks); i++) {
		ret = isc_clk_register(isc, i);
		if (ret)
			return ret;
	}

	return 0;
}