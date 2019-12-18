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
struct ti_sci_pm_domain {struct ti_sci_handle* ti_sci; } ;
struct TYPE_3__ {int (* is_valid ) (struct ti_sci_handle const*,int) ;} ;
struct TYPE_4__ {TYPE_1__ dev_ops; } ;
struct ti_sci_handle {TYPE_2__ ops; } ;
struct ti_sci_genpd_dev_data {int idx; int exclusive; } ;
struct of_phandle_args {int args_count; int* args; } ;
struct generic_pm_domain_data {struct ti_sci_genpd_dev_data* data; } ;
struct generic_pm_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TI_SCI_PD_EXCLUSIVE ; 
 struct generic_pm_domain_data* dev_gpd_data (struct device*) ; 
 struct ti_sci_pm_domain* genpd_to_ti_sci_pd (struct generic_pm_domain*) ; 
 struct ti_sci_genpd_dev_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int stub1 (struct ti_sci_handle const*,int) ; 

__attribute__((used)) static int ti_sci_pd_attach_dev(struct generic_pm_domain *domain,
				struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct of_phandle_args pd_args;
	struct ti_sci_pm_domain *ti_sci_genpd = genpd_to_ti_sci_pd(domain);
	const struct ti_sci_handle *ti_sci = ti_sci_genpd->ti_sci;
	struct ti_sci_genpd_dev_data *sci_dev_data;
	struct generic_pm_domain_data *genpd_data;
	int idx, ret = 0;

	ret = of_parse_phandle_with_args(np, "power-domains",
					 "#power-domain-cells", 0, &pd_args);
	if (ret < 0)
		return ret;

	if (pd_args.args_count != 1 && pd_args.args_count != 2)
		return -EINVAL;

	idx = pd_args.args[0];

	/*
	 * Check the validity of the requested idx, if the index is not valid
	 * the PMMC will return a NAK here and we will not allocate it.
	 */
	ret = ti_sci->ops.dev_ops.is_valid(ti_sci, idx);
	if (ret)
		return -EINVAL;

	sci_dev_data = kzalloc(sizeof(*sci_dev_data), GFP_KERNEL);
	if (!sci_dev_data)
		return -ENOMEM;

	sci_dev_data->idx = idx;
	/* Enable the exclusive permissions by default */
	sci_dev_data->exclusive = TI_SCI_PD_EXCLUSIVE;
	if (pd_args.args_count == 2)
		sci_dev_data->exclusive = pd_args.args[1] & 0x1;

	genpd_data = dev_gpd_data(dev);
	genpd_data->data = sci_dev_data;

	return 0;
}