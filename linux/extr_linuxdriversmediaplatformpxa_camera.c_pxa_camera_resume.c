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
struct pxa_camera_dev {int* save_cicr; scalar_t__ active; scalar_t__ sensor; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CICR0 ; 
 int CICR0_ENB ; 
 scalar_t__ CICR1 ; 
 scalar_t__ CICR2 ; 
 scalar_t__ CICR3 ; 
 scalar_t__ CICR4 ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 struct pxa_camera_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pxa_camera_start_capture (struct pxa_camera_dev*) ; 
 int pxac_sensor_set_power (struct pxa_camera_dev*,int) ; 

__attribute__((used)) static int pxa_camera_resume(struct device *dev)
{
	struct pxa_camera_dev *pcdev = dev_get_drvdata(dev);
	int i = 0, ret = 0;

	__raw_writel(pcdev->save_cicr[i++] & ~CICR0_ENB, pcdev->base + CICR0);
	__raw_writel(pcdev->save_cicr[i++], pcdev->base + CICR1);
	__raw_writel(pcdev->save_cicr[i++], pcdev->base + CICR2);
	__raw_writel(pcdev->save_cicr[i++], pcdev->base + CICR3);
	__raw_writel(pcdev->save_cicr[i++], pcdev->base + CICR4);

	if (pcdev->sensor) {
		ret = pxac_sensor_set_power(pcdev, 1);
	}

	/* Restart frame capture if active buffer exists */
	if (!ret && pcdev->active)
		pxa_camera_start_capture(pcdev);

	return ret;
}