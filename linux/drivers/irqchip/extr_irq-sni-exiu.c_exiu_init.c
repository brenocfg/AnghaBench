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
struct resource {int /*<<< orphan*/  start; } ;
struct fwnode_handle {int dummy; } ;
struct exiu_irq_data {scalar_t__ base; int /*<<< orphan*/  spi_base; } ;

/* Variables and functions */
 scalar_t__ EIMASK ; 
 scalar_t__ EIREQCLR ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct exiu_irq_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ fwnode_property_read_u32_array (struct fwnode_handle const*,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct exiu_irq_data*) ; 
 struct exiu_irq_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static struct exiu_irq_data *exiu_init(const struct fwnode_handle *fwnode,
				       struct resource *res)
{
	struct exiu_irq_data *data;
	int err;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return ERR_PTR(-ENOMEM);

	if (fwnode_property_read_u32_array(fwnode, "socionext,spi-base",
					   &data->spi_base, 1)) {
		err = -ENODEV;
		goto out_free;
	}

	data->base = ioremap(res->start, resource_size(res));
	if (!data->base) {
		err = -ENODEV;
		goto out_free;
	}

	/* clear and mask all interrupts */
	writel_relaxed(0xFFFFFFFF, data->base + EIREQCLR);
	writel_relaxed(0xFFFFFFFF, data->base + EIMASK);

	return data;

out_free:
	kfree(data);
	return ERR_PTR(err);
}