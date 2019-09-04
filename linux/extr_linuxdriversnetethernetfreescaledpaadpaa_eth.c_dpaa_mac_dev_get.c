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
struct device {struct dpaa_eth_data* platform_data; } ;
struct platform_device {struct device dev; } ;
struct mac_device {int dummy; } ;
struct dpaa_eth_data {struct mac_device* mac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct mac_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static struct mac_device *dpaa_mac_dev_get(struct platform_device *pdev)
{
	struct dpaa_eth_data *eth_data;
	struct device *dpaa_dev;
	struct mac_device *mac_dev;

	dpaa_dev = &pdev->dev;
	eth_data = dpaa_dev->platform_data;
	if (!eth_data) {
		dev_err(dpaa_dev, "eth_data missing\n");
		return ERR_PTR(-ENODEV);
	}
	mac_dev = eth_data->mac_dev;
	if (!mac_dev) {
		dev_err(dpaa_dev, "mac_dev missing\n");
		return ERR_PTR(-EINVAL);
	}

	return mac_dev;
}