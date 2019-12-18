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
typedef  int u32 ;
struct device {TYPE_1__* parent; } ;
struct platform_device {struct device dev; } ;
struct mxs_lradc_ts {int over_sample_cnt; int over_sample_delay; int settling_delay; int /*<<< orphan*/  base; struct device* dev; int /*<<< orphan*/  lock; struct mxs_lradc* lradc; } ;
struct mxs_lradc {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int LRADC_DELAY_DELAY_MASK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct mxs_lradc* dev_get_drvdata (TYPE_1__*) ; 
 struct mxs_lradc_ts* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mxs_lradc_ts*) ; 
 int irq_of_parse_and_map (struct device_node*,int) ; 
 int /*<<< orphan*/  mxs_lradc_ts_handle_irq ; 
 int /*<<< orphan*/  mxs_lradc_ts_hw_init (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/ * mxs_lradc_ts_irq_names ; 
 int mxs_lradc_ts_register (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_ts_stop (struct mxs_lradc_ts*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int platform_get_irq_byname (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stmp_reset_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxs_lradc_ts_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->parent->of_node;
	struct mxs_lradc *lradc = dev_get_drvdata(dev->parent);
	struct mxs_lradc_ts *ts;
	int ret, irq, virq, i;
	u32 ts_wires = 0, adapt;

	ts = devm_kzalloc(dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	platform_set_drvdata(pdev, ts);

	ts->lradc = lradc;
	ts->dev = dev;
	spin_lock_init(&ts->lock);

	ts->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(ts->base))
		return PTR_ERR(ts->base);

	ret = of_property_read_u32(node, "fsl,lradc-touchscreen-wires",
				   &ts_wires);
	if (ret)
		return ret;

	if (of_property_read_u32(node, "fsl,ave-ctrl", &adapt)) {
		ts->over_sample_cnt = 4;
	} else {
		if (adapt >= 1 && adapt <= 32) {
			ts->over_sample_cnt = adapt;
		} else {
			dev_err(ts->dev, "Invalid sample count (%u)\n",
				adapt);
			return -EINVAL;
		}
	}

	if (of_property_read_u32(node, "fsl,ave-delay", &adapt)) {
		ts->over_sample_delay = 2;
	} else {
		if (adapt >= 2 && adapt <= LRADC_DELAY_DELAY_MASK + 1) {
			ts->over_sample_delay = adapt;
		} else {
			dev_err(ts->dev, "Invalid sample delay (%u)\n",
				adapt);
			return -EINVAL;
		}
	}

	if (of_property_read_u32(node, "fsl,settling", &adapt)) {
		ts->settling_delay = 10;
	} else {
		if (adapt >= 1 && adapt <= LRADC_DELAY_DELAY_MASK) {
			ts->settling_delay = adapt;
		} else {
			dev_err(ts->dev, "Invalid settling delay (%u)\n",
				adapt);
			return -EINVAL;
		}
	}

	ret = stmp_reset_block(ts->base);
	if (ret)
		return ret;

	mxs_lradc_ts_hw_init(ts);

	for (i = 0; i < 3; i++) {
		irq = platform_get_irq_byname(pdev, mxs_lradc_ts_irq_names[i]);
		if (irq < 0)
			return irq;

		virq = irq_of_parse_and_map(node, irq);

		mxs_lradc_ts_stop(ts);

		ret = devm_request_irq(dev, virq,
				       mxs_lradc_ts_handle_irq,
				       0, mxs_lradc_ts_irq_names[i], ts);
		if (ret)
			return ret;
	}

	return mxs_lradc_ts_register(ts);
}