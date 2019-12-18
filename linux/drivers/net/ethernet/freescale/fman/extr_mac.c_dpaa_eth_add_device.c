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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mac_priv_s {int /*<<< orphan*/  dev; int /*<<< orphan*/  cell_index; } ;
struct mac_device {struct mac_priv_s* priv; } ;
struct dpaa_eth_data {int fman_hw_id; int /*<<< orphan*/  mac_hw_id; struct mac_device* mac_dev; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  eth_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct dpaa_eth_data*,int) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static struct platform_device *dpaa_eth_add_device(int fman_id,
						   struct mac_device *mac_dev)
{
	struct platform_device *pdev;
	struct dpaa_eth_data data;
	struct mac_priv_s	*priv;
	static int dpaa_eth_dev_cnt;
	int ret;

	priv = mac_dev->priv;

	data.mac_dev = mac_dev;
	data.mac_hw_id = priv->cell_index;
	data.fman_hw_id = fman_id;

	mutex_lock(&eth_lock);
	pdev = platform_device_alloc("dpaa-ethernet", dpaa_eth_dev_cnt);
	if (!pdev) {
		ret = -ENOMEM;
		goto no_mem;
	}

	pdev->dev.parent = priv->dev;

	ret = platform_device_add_data(pdev, &data, sizeof(data));
	if (ret)
		goto err;

	ret = platform_device_add(pdev);
	if (ret)
		goto err;

	dpaa_eth_dev_cnt++;
	mutex_unlock(&eth_lock);

	return pdev;

err:
	platform_device_put(pdev);
no_mem:
	mutex_unlock(&eth_lock);

	return ERR_PTR(ret);
}