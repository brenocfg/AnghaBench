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
struct sti_hdmi {int /*<<< orphan*/  notifier; scalar_t__ audio_pdev; int /*<<< orphan*/  ddc_adapt; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  cec_notifier_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sti_hdmi* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  sti_hdmi_ops ; 

__attribute__((used)) static int sti_hdmi_remove(struct platform_device *pdev)
{
	struct sti_hdmi *hdmi = dev_get_drvdata(&pdev->dev);

	cec_notifier_set_phys_addr(hdmi->notifier, CEC_PHYS_ADDR_INVALID);

	i2c_put_adapter(hdmi->ddc_adapt);
	if (hdmi->audio_pdev)
		platform_device_unregister(hdmi->audio_pdev);
	component_del(&pdev->dev, &sti_hdmi_ops);

	cec_notifier_put(hdmi->notifier);
	return 0;
}