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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP3952_LABEL_MAX_LEN ; 
 int device_property_read_string (struct device*,char const*,char const**) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp3952_get_label(struct device *dev, const char *label, char *dest)
{
	int ret;
	const char *str;

	ret = device_property_read_string(dev, label, &str);
	if (ret)
		return ret;

	strncpy(dest, str, LP3952_LABEL_MAX_LEN);
	return 0;
}