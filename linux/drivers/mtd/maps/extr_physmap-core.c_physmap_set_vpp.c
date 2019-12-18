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
struct physmap_flash_info {int vpp_refcnt; int /*<<< orphan*/  vpp_lock; } ;
struct physmap_flash_data {int /*<<< orphan*/  (* set_vpp ) (struct platform_device*,int) ;} ;
struct map_info {scalar_t__ map_priv_1; } ;

/* Variables and functions */
 struct physmap_flash_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct physmap_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct platform_device*,int) ; 

__attribute__((used)) static void physmap_set_vpp(struct map_info *map, int state)
{
	struct platform_device *pdev;
	struct physmap_flash_data *physmap_data;
	struct physmap_flash_info *info;
	unsigned long flags;

	pdev = (struct platform_device *)map->map_priv_1;
	physmap_data = dev_get_platdata(&pdev->dev);

	if (!physmap_data->set_vpp)
		return;

	info = platform_get_drvdata(pdev);

	spin_lock_irqsave(&info->vpp_lock, flags);
	if (state) {
		if (++info->vpp_refcnt == 1)    /* first nested 'on' */
			physmap_data->set_vpp(pdev, 1);
	} else {
		if (--info->vpp_refcnt == 0)    /* last nested 'off' */
			physmap_data->set_vpp(pdev, 0);
	}
	spin_unlock_irqrestore(&info->vpp_lock, flags);
}