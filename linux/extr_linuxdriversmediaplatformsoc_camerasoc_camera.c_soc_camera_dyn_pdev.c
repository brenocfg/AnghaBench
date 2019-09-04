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
struct soc_camera_desc {int dummy; } ;
struct soc_camera_async_client {struct platform_device* pdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAP_MAX_NUM ; 
 int /*<<< orphan*/  device_map ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int platform_device_add_data (struct platform_device*,struct soc_camera_desc*,int) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_camera_dyn_pdev(struct soc_camera_desc *sdesc,
			       struct soc_camera_async_client *sasc)
{
	struct platform_device *pdev;
	int ret, i;

	mutex_lock(&list_lock);
	i = find_first_zero_bit(device_map, MAP_MAX_NUM);
	if (i < MAP_MAX_NUM)
		set_bit(i, device_map);
	mutex_unlock(&list_lock);
	if (i >= MAP_MAX_NUM)
		return -ENOMEM;

	pdev = platform_device_alloc("soc-camera-pdrv", i);
	if (!pdev)
		return -ENOMEM;

	ret = platform_device_add_data(pdev, sdesc, sizeof(*sdesc));
	if (ret < 0) {
		platform_device_put(pdev);
		return ret;
	}

	sasc->pdev = pdev;

	return 0;
}