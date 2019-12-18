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
struct intel_pinctrl_soc_data {int ncommunities; struct intel_community* communities; } ;
struct intel_community {int /*<<< orphan*/  pad_regs; } ;
struct byt_gpio {TYPE_1__* pdev; struct intel_pinctrl_soc_data const* soc_data; struct intel_community* communities_copy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct intel_community* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int byt_set_soc_data(struct byt_gpio *vg,
			    const struct intel_pinctrl_soc_data *soc_data)
{
	int i;

	vg->soc_data = soc_data;
	vg->communities_copy = devm_kcalloc(&vg->pdev->dev,
					    soc_data->ncommunities,
					    sizeof(*vg->communities_copy),
					    GFP_KERNEL);
	if (!vg->communities_copy)
		return -ENOMEM;

	for (i = 0; i < soc_data->ncommunities; i++) {
		struct intel_community *comm = vg->communities_copy + i;

		*comm = vg->soc_data->communities[i];

		comm->pad_regs = devm_platform_ioremap_resource(vg->pdev, 0);
		if (IS_ERR(comm->pad_regs))
			return PTR_ERR(comm->pad_regs);
	}

	return 0;
}