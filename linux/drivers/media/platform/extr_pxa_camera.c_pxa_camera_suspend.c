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
struct pxa_camera_dev {scalar_t__ sensor; scalar_t__ base; void** save_cicr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CICR0 ; 
 scalar_t__ CICR1 ; 
 scalar_t__ CICR2 ; 
 scalar_t__ CICR3 ; 
 scalar_t__ CICR4 ; 
 void* __raw_readl (scalar_t__) ; 
 struct pxa_camera_dev* dev_get_drvdata (struct device*) ; 
 int pxac_sensor_set_power (struct pxa_camera_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_camera_suspend(struct device *dev)
{
	struct pxa_camera_dev *pcdev = dev_get_drvdata(dev);
	int i = 0, ret = 0;

	pcdev->save_cicr[i++] = __raw_readl(pcdev->base + CICR0);
	pcdev->save_cicr[i++] = __raw_readl(pcdev->base + CICR1);
	pcdev->save_cicr[i++] = __raw_readl(pcdev->base + CICR2);
	pcdev->save_cicr[i++] = __raw_readl(pcdev->base + CICR3);
	pcdev->save_cicr[i++] = __raw_readl(pcdev->base + CICR4);

	if (pcdev->sensor)
		ret = pxac_sensor_set_power(pcdev, 0);

	return ret;
}