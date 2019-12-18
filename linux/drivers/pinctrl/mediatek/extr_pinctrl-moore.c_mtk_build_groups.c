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
struct mtk_pinctrl {int /*<<< orphan*/  dev; int /*<<< orphan*/  pctrl; TYPE_1__* soc; } ;
struct group_desc {int /*<<< orphan*/  name; int /*<<< orphan*/  data; int /*<<< orphan*/  num_pins; int /*<<< orphan*/  pins; } ;
struct TYPE_2__ {int ngrps; struct group_desc* grps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pinctrl_generic_add_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_build_groups(struct mtk_pinctrl *hw)
{
	int err, i;

	for (i = 0; i < hw->soc->ngrps; i++) {
		const struct group_desc *group = hw->soc->grps + i;

		err = pinctrl_generic_add_group(hw->pctrl, group->name,
						group->pins, group->num_pins,
						group->data);
		if (err < 0) {
			dev_err(hw->dev, "Failed to register group %s\n",
				group->name);
			return err;
		}
	}

	return 0;
}