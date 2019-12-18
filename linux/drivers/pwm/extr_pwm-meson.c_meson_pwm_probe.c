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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int base; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/  npwm; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct meson_pwm {TYPE_1__ chip; int /*<<< orphan*/  data; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESON_NUM_PWMS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct meson_pwm* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int meson_pwm_init_channels (struct meson_pwm*) ; 
 int /*<<< orphan*/  meson_pwm_ops ; 
 int /*<<< orphan*/  of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_pwm*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_pwm_probe(struct platform_device *pdev)
{
	struct meson_pwm *meson;
	struct resource *regs;
	int err;

	meson = devm_kzalloc(&pdev->dev, sizeof(*meson), GFP_KERNEL);
	if (!meson)
		return -ENOMEM;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	meson->base = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(meson->base))
		return PTR_ERR(meson->base);

	spin_lock_init(&meson->lock);
	meson->chip.dev = &pdev->dev;
	meson->chip.ops = &meson_pwm_ops;
	meson->chip.base = -1;
	meson->chip.npwm = MESON_NUM_PWMS;
	meson->chip.of_xlate = of_pwm_xlate_with_flags;
	meson->chip.of_pwm_n_cells = 3;

	meson->data = of_device_get_match_data(&pdev->dev);

	err = meson_pwm_init_channels(meson);
	if (err < 0)
		return err;

	err = pwmchip_add(&meson->chip);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to register PWM chip: %d\n", err);
		return err;
	}

	platform_set_drvdata(pdev, meson);

	return 0;
}