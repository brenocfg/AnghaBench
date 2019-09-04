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
struct i2c_adapter {int dummy; } ;
struct hdmi_i2c_adapter {int /*<<< orphan*/  ddc_event; } ;

/* Variables and functions */
 scalar_t__ sw_done (struct hdmi_i2c_adapter*) ; 
 struct hdmi_i2c_adapter* to_hdmi_i2c_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void msm_hdmi_i2c_irq(struct i2c_adapter *i2c)
{
	struct hdmi_i2c_adapter *hdmi_i2c = to_hdmi_i2c_adapter(i2c);

	if (sw_done(hdmi_i2c))
		wake_up_all(&hdmi_i2c->ddc_event);
}