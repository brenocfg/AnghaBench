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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct mmc_pwrseq_simple {TYPE_1__ pwrseq; int /*<<< orphan*/  power_off_delay_us; int /*<<< orphan*/  post_power_on_delay_ms; int /*<<< orphan*/  reset_gpios; int /*<<< orphan*/  ext_clk; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_array (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct mmc_pwrseq_simple* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int mmc_pwrseq_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_pwrseq_simple_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_pwrseq_simple*) ; 

__attribute__((used)) static int mmc_pwrseq_simple_probe(struct platform_device *pdev)
{
	struct mmc_pwrseq_simple *pwrseq;
	struct device *dev = &pdev->dev;

	pwrseq = devm_kzalloc(dev, sizeof(*pwrseq), GFP_KERNEL);
	if (!pwrseq)
		return -ENOMEM;

	pwrseq->ext_clk = devm_clk_get(dev, "ext_clock");
	if (IS_ERR(pwrseq->ext_clk) && PTR_ERR(pwrseq->ext_clk) != -ENOENT)
		return PTR_ERR(pwrseq->ext_clk);

	pwrseq->reset_gpios = devm_gpiod_get_array(dev, "reset",
							GPIOD_OUT_HIGH);
	if (IS_ERR(pwrseq->reset_gpios) &&
	    PTR_ERR(pwrseq->reset_gpios) != -ENOENT &&
	    PTR_ERR(pwrseq->reset_gpios) != -ENOSYS) {
		return PTR_ERR(pwrseq->reset_gpios);
	}

	device_property_read_u32(dev, "post-power-on-delay-ms",
				 &pwrseq->post_power_on_delay_ms);
	device_property_read_u32(dev, "power-off-delay-us",
				 &pwrseq->power_off_delay_us);

	pwrseq->pwrseq.dev = dev;
	pwrseq->pwrseq.ops = &mmc_pwrseq_simple_ops;
	pwrseq->pwrseq.owner = THIS_MODULE;
	platform_set_drvdata(pdev, pwrseq);

	return mmc_pwrseq_register(&pwrseq->pwrseq);
}