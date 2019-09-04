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
typedef  int /*<<< orphan*/  u8 ;
struct resources {int /*<<< orphan*/ * regulator; scalar_t__** clock_rate; int /*<<< orphan*/ * clock; int /*<<< orphan*/ * interrupt; int /*<<< orphan*/ * reg; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;
struct csid_device {size_t nclocks; int /*<<< orphan*/  reset_complete; int /*<<< orphan*/  vdda; struct camss_clock* clock; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_name; int /*<<< orphan*/  id; int /*<<< orphan*/  base; void* nformats; void* formats; struct camss* camss; } ;
struct camss_clock {size_t nfreqs; scalar_t__* freq; int /*<<< orphan*/  name; int /*<<< orphan*/  clk; } ;
struct camss {scalar_t__ version; struct device* dev; } ;

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
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 char* MSM_CSID_NAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* csid_formats_8x16 ; 
 void* csid_formats_8x96 ; 
 int /*<<< orphan*/  csid_isr ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kcalloc (struct device*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct csid_device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int msm_csid_subdev_init(struct camss *camss, struct csid_device *csid,
			 const struct resources *res, u8 id)
{
	struct device *dev = camss->dev;
	struct platform_device *pdev = to_platform_device(dev);
	struct resource *r;
	int i, j;
	int ret;

	csid->camss = camss;
	csid->id = id;

	if (camss->version == CAMSS_8x16) {
		csid->formats = csid_formats_8x16;
		csid->nformats =
				ARRAY_SIZE(csid_formats_8x16);
	} else if (camss->version == CAMSS_8x96) {
		csid->formats = csid_formats_8x96;
		csid->nformats =
				ARRAY_SIZE(csid_formats_8x96);
	} else {
		return -EINVAL;
	}

	/* Memory */

	r = platform_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[0]);
	csid->base = devm_ioremap_resource(dev, r);
	if (IS_ERR(csid->base)) {
		dev_err(dev, "could not map memory\n");
		return PTR_ERR(csid->base);
	}

	/* Interrupt */

	r = platform_get_resource_byname(pdev, IORESOURCE_IRQ,
					 res->interrupt[0]);
	if (!r) {
		dev_err(dev, "missing IRQ\n");
		return -EINVAL;
	}

	csid->irq = r->start;
	snprintf(csid->irq_name, sizeof(csid->irq_name), "%s_%s%d",
		 dev_name(dev), MSM_CSID_NAME, csid->id);
	ret = devm_request_irq(dev, csid->irq, csid_isr,
		IRQF_TRIGGER_RISING, csid->irq_name, csid);
	if (ret < 0) {
		dev_err(dev, "request_irq failed: %d\n", ret);
		return ret;
	}

	disable_irq(csid->irq);

	/* Clocks */

	csid->nclocks = 0;
	while (res->clock[csid->nclocks])
		csid->nclocks++;

	csid->clock = devm_kcalloc(dev, csid->nclocks, sizeof(*csid->clock),
				    GFP_KERNEL);
	if (!csid->clock)
		return -ENOMEM;

	for (i = 0; i < csid->nclocks; i++) {
		struct camss_clock *clock = &csid->clock[i];

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

	/* Regulator */

	csid->vdda = devm_regulator_get(dev, res->regulator[0]);
	if (IS_ERR(csid->vdda)) {
		dev_err(dev, "could not get regulator\n");
		return PTR_ERR(csid->vdda);
	}

	init_completion(&csid->reset_complete);

	return 0;
}