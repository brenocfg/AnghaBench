#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct resources {scalar_t__** clock_rate; int /*<<< orphan*/ * clock; int /*<<< orphan*/ * interrupt; int /*<<< orphan*/ * reg; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ combo_mode; } ;
struct csiphy_device {size_t nclocks; struct camss_clock* clock; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_name; TYPE_2__* ops; int /*<<< orphan*/  id; void* base_clk_mux; void* base; void* nformats; void* formats; TYPE_1__ cfg; struct camss* camss; } ;
struct camss_clock {size_t nfreqs; scalar_t__* freq; int /*<<< orphan*/  name; void* clk; } ;
struct camss {scalar_t__ version; struct device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  isr; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 scalar_t__ CAMSS_8x16 ; 
 scalar_t__ CAMSS_8x96 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 char* MSM_CSIPHY_NAME ; 
 int PTR_ERR (void*) ; 
 void* csiphy_formats_8x16 ; 
 void* csiphy_formats_8x96 ; 
 TYPE_2__ csiphy_ops_2ph_1_0 ; 
 TYPE_2__ csiphy_ops_3ph_1_0 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kcalloc (struct device*,size_t,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct csiphy_device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int msm_csiphy_subdev_init(struct camss *camss,
			   struct csiphy_device *csiphy,
			   const struct resources *res, u8 id)
{
	struct device *dev = camss->dev;
	struct platform_device *pdev = to_platform_device(dev);
	struct resource *r;
	int i, j;
	int ret;

	csiphy->camss = camss;
	csiphy->id = id;
	csiphy->cfg.combo_mode = 0;

	if (camss->version == CAMSS_8x16) {
		csiphy->ops = &csiphy_ops_2ph_1_0;
		csiphy->formats = csiphy_formats_8x16;
		csiphy->nformats = ARRAY_SIZE(csiphy_formats_8x16);
	} else if (camss->version == CAMSS_8x96) {
		csiphy->ops = &csiphy_ops_3ph_1_0;
		csiphy->formats = csiphy_formats_8x96;
		csiphy->nformats = ARRAY_SIZE(csiphy_formats_8x96);
	} else {
		return -EINVAL;
	}

	/* Memory */

	r = platform_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[0]);
	csiphy->base = devm_ioremap_resource(dev, r);
	if (IS_ERR(csiphy->base)) {
		dev_err(dev, "could not map memory\n");
		return PTR_ERR(csiphy->base);
	}

	r = platform_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[1]);
	csiphy->base_clk_mux = devm_ioremap_resource(dev, r);
	if (IS_ERR(csiphy->base_clk_mux)) {
		dev_err(dev, "could not map memory\n");
		return PTR_ERR(csiphy->base_clk_mux);
	}

	/* Interrupt */

	r = platform_get_resource_byname(pdev, IORESOURCE_IRQ,
					 res->interrupt[0]);
	if (!r) {
		dev_err(dev, "missing IRQ\n");
		return -EINVAL;
	}

	csiphy->irq = r->start;
	snprintf(csiphy->irq_name, sizeof(csiphy->irq_name), "%s_%s%d",
		 dev_name(dev), MSM_CSIPHY_NAME, csiphy->id);

	ret = devm_request_irq(dev, csiphy->irq, csiphy->ops->isr,
			       IRQF_TRIGGER_RISING, csiphy->irq_name, csiphy);
	if (ret < 0) {
		dev_err(dev, "request_irq failed: %d\n", ret);
		return ret;
	}

	disable_irq(csiphy->irq);

	/* Clocks */

	csiphy->nclocks = 0;
	while (res->clock[csiphy->nclocks])
		csiphy->nclocks++;

	csiphy->clock = devm_kcalloc(dev,
				     csiphy->nclocks, sizeof(*csiphy->clock),
				     GFP_KERNEL);
	if (!csiphy->clock)
		return -ENOMEM;

	for (i = 0; i < csiphy->nclocks; i++) {
		struct camss_clock *clock = &csiphy->clock[i];

		clock->clk = devm_clk_get(dev, res->clock[i]);
		if (IS_ERR(clock->clk))
			return PTR_ERR(clock->clk);

		clock->name = res->clock[i];

		clock->nfreqs = 0;
		while (res->clock_rate[i][clock->nfreqs])
			clock->nfreqs++;

		if (!clock->nfreqs) {
			clock->freq = NULL;
			continue;
		}

		clock->freq = devm_kcalloc(dev,
					   clock->nfreqs,
					   sizeof(*clock->freq),
					   GFP_KERNEL);
		if (!clock->freq)
			return -ENOMEM;

		for (j = 0; j < clock->nfreqs; j++)
			clock->freq[j] = res->clock_rate[i][j];
	}

	return 0;
}