#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ocelot_pinctrl {TYPE_3__* desc; TYPE_1__* func; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int npins; TYPE_2__* pins; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int ngroups; int /*<<< orphan*/ * groups; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FUNC_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 size_t* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 scalar_t__ ocelot_pin_function_idx (struct ocelot_pinctrl*,int,int) ; 

__attribute__((used)) static int ocelot_create_group_func_map(struct device *dev,
					struct ocelot_pinctrl *info)
{
	int f, npins, i;
	u8 *pins = kcalloc(info->desc->npins, sizeof(u8), GFP_KERNEL);

	if (!pins)
		return -ENOMEM;

	for (f = 0; f < FUNC_MAX; f++) {
		for (npins = 0, i = 0; i < info->desc->npins; i++) {
			if (ocelot_pin_function_idx(info, i, f) >= 0)
				pins[npins++] = i;
		}

		if (!npins)
			continue;

		info->func[f].ngroups = npins;
		info->func[f].groups = devm_kcalloc(dev, npins, sizeof(char *),
						    GFP_KERNEL);
		if (!info->func[f].groups) {
			kfree(pins);
			return -ENOMEM;
		}

		for (i = 0; i < npins; i++)
			info->func[f].groups[i] = info->desc->pins[pins[i]].name;
	}

	kfree(pins);

	return 0;
}