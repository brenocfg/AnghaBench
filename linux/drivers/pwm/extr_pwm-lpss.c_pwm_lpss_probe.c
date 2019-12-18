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
struct resource {int dummy; } ;
struct TYPE_2__ {int base; scalar_t__ npwm; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct pwm_lpss_chip {TYPE_1__ chip; struct pwm_lpss_boardinfo const* info; int /*<<< orphan*/  regs; } ;
struct pwm_lpss_boardinfo {scalar_t__ npwm; unsigned long clk_rate; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct pwm_lpss_chip* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct pwm_lpss_chip* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_PWMS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct pwm_lpss_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_lpss_ops ; 
 int pwmchip_add (TYPE_1__*) ; 

struct pwm_lpss_chip *pwm_lpss_probe(struct device *dev, struct resource *r,
				     const struct pwm_lpss_boardinfo *info)
{
	struct pwm_lpss_chip *lpwm;
	unsigned long c;
	int ret;

	if (WARN_ON(info->npwm > MAX_PWMS))
		return ERR_PTR(-ENODEV);

	lpwm = devm_kzalloc(dev, sizeof(*lpwm), GFP_KERNEL);
	if (!lpwm)
		return ERR_PTR(-ENOMEM);

	lpwm->regs = devm_ioremap_resource(dev, r);
	if (IS_ERR(lpwm->regs))
		return ERR_CAST(lpwm->regs);

	lpwm->info = info;

	c = lpwm->info->clk_rate;
	if (!c)
		return ERR_PTR(-EINVAL);

	lpwm->chip.dev = dev;
	lpwm->chip.ops = &pwm_lpss_ops;
	lpwm->chip.base = -1;
	lpwm->chip.npwm = info->npwm;

	ret = pwmchip_add(&lpwm->chip);
	if (ret) {
		dev_err(dev, "failed to add PWM chip: %d\n", ret);
		return ERR_PTR(ret);
	}

	return lpwm;
}