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
struct samsung_laptop {struct sabi_config* config; } ;
struct sabi_performance_level {scalar_t__ name; int /*<<< orphan*/  value; } ;
struct sabi_commands {int /*<<< orphan*/  set_performance_level; } ;
struct sabi_config {struct sabi_performance_level* performance_levels; struct sabi_commands commands; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct samsung_laptop* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sabi_set_commandb (struct samsung_laptop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncasecmp (scalar_t__,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t set_performance_level(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
	struct samsung_laptop *samsung = dev_get_drvdata(dev);
	const struct sabi_config *config = samsung->config;
	const struct sabi_commands *commands = &config->commands;
	int i;

	if (count < 1)
		return count;

	for (i = 0; config->performance_levels[i].name; ++i) {
		const struct sabi_performance_level *level =
			&config->performance_levels[i];
		if (!strncasecmp(level->name, buf, strlen(level->name))) {
			sabi_set_commandb(samsung,
					  commands->set_performance_level,
					  level->value);
			break;
		}
	}

	if (!config->performance_levels[i].name)
		return -EINVAL;

	return count;
}