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
struct uea_softc {int reset; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 struct uea_softc* dev_to_uea (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_mutex ; 

__attribute__((used)) static ssize_t stat_status_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int ret = -ENODEV;
	struct uea_softc *sc;

	mutex_lock(&uea_mutex);
	sc = dev_to_uea(dev);
	if (!sc)
		goto out;
	sc->reset = 1;
	ret = count;
out:
	mutex_unlock(&uea_mutex);
	return ret;
}