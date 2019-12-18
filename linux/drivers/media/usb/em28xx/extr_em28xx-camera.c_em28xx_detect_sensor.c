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
struct em28xx {scalar_t__ em28xx_sensor; TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EM28XX_NOSENSOR ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int em28xx_probe_sensor_micron (struct em28xx*) ; 
 int em28xx_probe_sensor_omnivision (struct em28xx*) ; 

int em28xx_detect_sensor(struct em28xx *dev)
{
	int ret;

	ret = em28xx_probe_sensor_micron(dev);

	if (dev->em28xx_sensor == EM28XX_NOSENSOR && ret < 0)
		ret = em28xx_probe_sensor_omnivision(dev);

	/*
	 * NOTE: the Windows driver also probes i2c addresses
	 *       0x22 (Samsung ?) and 0x66 (Kodak ?)
	 */

	if (dev->em28xx_sensor == EM28XX_NOSENSOR && ret < 0) {
		dev_info(&dev->intf->dev,
			 "No sensor detected\n");
		return -ENODEV;
	}

	return 0;
}