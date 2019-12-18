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
struct meson_vrtc_data {unsigned int enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct meson_vrtc_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int meson_vrtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct meson_vrtc_data *vrtc = dev_get_drvdata(dev);

	vrtc->enabled = enabled;
	return 0;
}