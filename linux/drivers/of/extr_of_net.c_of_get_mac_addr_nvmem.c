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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 void const* ERR_PTR (int) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int nvmem_get_mac_address (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const void *of_get_mac_addr_nvmem(struct device_node *np)
{
	int ret;
	const void *mac;
	u8 nvmem_mac[ETH_ALEN];
	struct platform_device *pdev = of_find_device_by_node(np);

	if (!pdev)
		return ERR_PTR(-ENODEV);

	ret = nvmem_get_mac_address(&pdev->dev, &nvmem_mac);
	if (ret) {
		put_device(&pdev->dev);
		return ERR_PTR(ret);
	}

	mac = devm_kmemdup(&pdev->dev, nvmem_mac, ETH_ALEN, GFP_KERNEL);
	put_device(&pdev->dev);
	if (!mac)
		return ERR_PTR(-ENOMEM);

	return mac;
}