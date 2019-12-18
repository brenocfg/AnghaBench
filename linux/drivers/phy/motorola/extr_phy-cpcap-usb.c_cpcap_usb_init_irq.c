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
struct platform_device {int dummy; } ;
struct cpcap_phy_ddata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  cpcap_phy_irq_thread ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct cpcap_phy_ddata*) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 

__attribute__((used)) static int cpcap_usb_init_irq(struct platform_device *pdev,
			      struct cpcap_phy_ddata *ddata,
			      const char *name)
{
	int irq, error;

	irq = platform_get_irq_byname(pdev, name);
	if (irq < 0)
		return -ENODEV;

	error = devm_request_threaded_irq(ddata->dev, irq, NULL,
					  cpcap_phy_irq_thread,
					  IRQF_SHARED,
					  name, ddata);
	if (error) {
		dev_err(ddata->dev, "could not get irq %s: %i\n",
			name, error);

		return error;
	}

	return 0;
}