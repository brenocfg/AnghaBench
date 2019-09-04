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
struct transient_trig_data {int /*<<< orphan*/  state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 struct transient_trig_data* led_trigger_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t transient_state_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct transient_trig_data *transient_data =
		led_trigger_get_drvdata(dev);
	int state;

	state = (transient_data->state == LED_FULL) ? 1 : 0;
	return sprintf(buf, "%d\n", state);
}