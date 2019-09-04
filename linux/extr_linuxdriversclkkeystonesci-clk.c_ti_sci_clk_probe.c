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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int (* get_num_parents ) (struct ti_sci_handle const*,int,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {TYPE_2__ clk_ops; } ;
struct ti_sci_handle {TYPE_1__ ops; } ;
struct sci_clk_provider {int num_clocks; struct sci_clk** clocks; struct ti_sci_handle const* sci; TYPE_2__* ops; struct device* dev; } ;
struct sci_clk {int dev_id; int clk_id; int /*<<< orphan*/  num_parents; struct sci_clk_provider* provider; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  sci_clk ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ti_sci_handle const*) ; 
 int PTR_ERR (struct ti_sci_handle const*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct sci_clk**) ; 
 void* devm_kmalloc_array (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct ti_sci_handle* devm_ti_sci_get_handle (struct device*) ; 
 int /*<<< orphan*/  memcpy (struct sci_clk**,struct sci_clk**,int) ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,struct sci_clk_provider*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sci_clk_get ; 
 int stub1 (struct ti_sci_handle const*,int,int,int /*<<< orphan*/ *) ; 
 int ti_sci_init_clocks (struct sci_clk_provider*) ; 

__attribute__((used)) static int ti_sci_clk_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct sci_clk_provider *provider;
	const struct ti_sci_handle *handle;
	int ret;
	int num_clks = 0;
	struct sci_clk **clks = NULL;
	struct sci_clk **tmp_clks;
	struct sci_clk *sci_clk;
	int max_clks = 0;
	int clk_id = 0;
	int dev_id = 0;
	u8 num_parents;
	int gap_size = 0;

	handle = devm_ti_sci_get_handle(dev);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	provider = devm_kzalloc(dev, sizeof(*provider), GFP_KERNEL);
	if (!provider)
		return -ENOMEM;

	provider->sci = handle;
	provider->ops = &handle->ops.clk_ops;
	provider->dev = dev;

	while (1) {
		ret = provider->ops->get_num_parents(provider->sci, dev_id,
						     clk_id, &num_parents);
		if (ret) {
			gap_size++;
			if (!clk_id) {
				if (gap_size >= 5)
					break;
				dev_id++;
			} else {
				if (gap_size >= 2) {
					dev_id++;
					clk_id = 0;
					gap_size = 0;
				} else {
					clk_id++;
				}
			}
			continue;
		}

		gap_size = 0;

		if (num_clks == max_clks) {
			tmp_clks = devm_kmalloc_array(dev, max_clks + 64,
						      sizeof(sci_clk),
						      GFP_KERNEL);
			memcpy(tmp_clks, clks, max_clks * sizeof(sci_clk));
			if (max_clks)
				devm_kfree(dev, clks);
			max_clks += 64;
			clks = tmp_clks;
		}

		sci_clk = devm_kzalloc(dev, sizeof(*sci_clk), GFP_KERNEL);
		if (!sci_clk)
			return -ENOMEM;
		sci_clk->dev_id = dev_id;
		sci_clk->clk_id = clk_id;
		sci_clk->provider = provider;
		sci_clk->num_parents = num_parents;

		clks[num_clks] = sci_clk;

		clk_id++;
		num_clks++;
	}

	provider->clocks = devm_kmalloc_array(dev, num_clks, sizeof(sci_clk),
					      GFP_KERNEL);
	if (!provider->clocks)
		return -ENOMEM;

	memcpy(provider->clocks, clks, num_clks * sizeof(sci_clk));

	provider->num_clocks = num_clks;

	devm_kfree(dev, clks);

	ret = ti_sci_init_clocks(provider);
	if (ret) {
		pr_err("ti-sci-init-clocks failed.\n");
		return ret;
	}

	return of_clk_add_hw_provider(np, sci_clk_get, provider);
}