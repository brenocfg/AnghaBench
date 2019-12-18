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
struct siox_device {int /*<<< orphan*/  dev; } ;
struct gpio_siox_ddata {int /*<<< orphan*/  lock; int /*<<< orphan*/ * setdata; } ;

/* Variables and functions */
 struct gpio_siox_ddata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_siox_set_data(struct siox_device *sdevice, u8 status, u8 buf[])
{
	struct gpio_siox_ddata *ddata = dev_get_drvdata(&sdevice->dev);

	mutex_lock(&ddata->lock);
	buf[0] = ddata->setdata[0];
	mutex_unlock(&ddata->lock);

	return 0;
}