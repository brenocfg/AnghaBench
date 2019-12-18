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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hisi_sas_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_sas_v2_hw ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_sas_v2_probe(struct platform_device *pdev)
{
	/*
	 * Check if we should defer the probe before we probe the
	 * upper layer, as it's hard to defer later on.
	 */
	int ret = platform_get_irq(pdev, 0);

	if (ret < 0) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "cannot obtain irq\n");
		return ret;
	}

	return hisi_sas_probe(pdev, &hisi_sas_v2_hw);
}