#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct meson_vrtc_data {TYPE_1__* rtc; TYPE_1__* io_alarm; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct meson_vrtc_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meson_vrtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_vrtc_data*) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int meson_vrtc_probe(struct platform_device *pdev)
{
	struct meson_vrtc_data *vrtc;
	int ret;

	vrtc = devm_kzalloc(&pdev->dev, sizeof(*vrtc), GFP_KERNEL);
	if (!vrtc)
		return -ENOMEM;

	vrtc->io_alarm = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(vrtc->io_alarm))
		return PTR_ERR(vrtc->io_alarm);

	device_init_wakeup(&pdev->dev, 1);

	platform_set_drvdata(pdev, vrtc);

	vrtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(vrtc->rtc))
		return PTR_ERR(vrtc->rtc);

	vrtc->rtc->ops = &meson_vrtc_ops;
	ret = rtc_register_device(vrtc->rtc);
	if (ret)
		return ret;

	return 0;
}