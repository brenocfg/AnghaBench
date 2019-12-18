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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acx565akm_panel {int /*<<< orphan*/  mutex; int /*<<< orphan*/  has_cabc; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 size_t EINVAL ; 
 char** acx565akm_cabc_modes ; 
 int /*<<< orphan*/  acx565akm_set_cabc_mode (struct acx565akm_panel*,unsigned int) ; 
 struct acx565akm_panel* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static ssize_t cabc_mode_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct acx565akm_panel *lcd = dev_get_drvdata(dev);
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(acx565akm_cabc_modes); i++) {
		const char *mode_str = acx565akm_cabc_modes[i];
		int cmp_len = strlen(mode_str);

		if (count > 0 && buf[count - 1] == '\n')
			count--;
		if (count != cmp_len)
			continue;

		if (strncmp(buf, mode_str, cmp_len) == 0)
			break;
	}

	if (i == ARRAY_SIZE(acx565akm_cabc_modes))
		return -EINVAL;

	if (!lcd->has_cabc && i != 0)
		return -EINVAL;

	mutex_lock(&lcd->mutex);
	acx565akm_set_cabc_mode(lcd, i);
	mutex_unlock(&lcd->mutex);

	return count;
}