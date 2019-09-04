#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ srst_udelay; int /*<<< orphan*/  quirks; } ;
struct sysc {TYPE_1__ cfg; TYPE_3__* dev; void* legacy_mode; } ;
struct property {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 TYPE_2__* sysc_dts_quirks ; 

__attribute__((used)) static int sysc_init_dts_quirks(struct sysc *ddata)
{
	struct device_node *np = ddata->dev->of_node;
	const struct property *prop;
	int i, len, error;
	u32 val;

	ddata->legacy_mode = of_get_property(np, "ti,hwmods", NULL);

	for (i = 0; i < ARRAY_SIZE(sysc_dts_quirks); i++) {
		prop = of_get_property(np, sysc_dts_quirks[i].name, &len);
		if (!prop)
			continue;

		ddata->cfg.quirks |= sysc_dts_quirks[i].mask;
	}

	error = of_property_read_u32(np, "ti,sysc-delay-us", &val);
	if (!error) {
		if (val > 255) {
			dev_warn(ddata->dev, "bad ti,sysc-delay-us: %i\n",
				 val);
		}

		ddata->cfg.srst_udelay = (u8)val;
	}

	return 0;
}