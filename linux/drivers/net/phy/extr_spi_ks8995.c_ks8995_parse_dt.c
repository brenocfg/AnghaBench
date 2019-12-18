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
struct ks8995_switch {struct ks8995_pdata* pdata; TYPE_2__* spi; } ;
struct ks8995_pdata {int /*<<< orphan*/  reset_gpio_flags; int /*<<< orphan*/  reset_gpio; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_get_named_gpio_flags (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ks8995_parse_dt(struct ks8995_switch *ks)
{
	struct device_node *np = ks->spi->dev.of_node;
	struct ks8995_pdata *pdata = ks->pdata;

	if (!np)
		return;

	pdata->reset_gpio = of_get_named_gpio_flags(np, "reset-gpios", 0,
		&pdata->reset_gpio_flags);
}