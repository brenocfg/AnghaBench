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
typedef  int /*<<< orphan*/  u32 ;
struct hwmon_channel_info {int type; int /*<<< orphan*/ * config; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scmi_hwmon_add_chan_info(struct hwmon_channel_info *scmi_hwmon_chan,
				    struct device *dev, int num,
				    enum hwmon_sensor_types type, u32 config)
{
	int i;
	u32 *cfg = devm_kcalloc(dev, num + 1, sizeof(*cfg), GFP_KERNEL);

	if (!cfg)
		return -ENOMEM;

	scmi_hwmon_chan->type = type;
	scmi_hwmon_chan->config = cfg;
	for (i = 0; i < num; i++, cfg++)
		*cfg = config;

	return 0;
}