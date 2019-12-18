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
struct i2400m {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 size_t i2400m_set_idle_timeout (struct i2400m*,unsigned int) ; 
 struct i2400m* net_dev_to_i2400m (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static
ssize_t i2400m_idle_timeout_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t size)
{
	ssize_t result;
	struct i2400m *i2400m = net_dev_to_i2400m(to_net_dev(dev));
	unsigned val;

	result = -EINVAL;
	if (sscanf(buf, "%u\n", &val) != 1)
		goto error_no_unsigned;
	if (val != 0 && (val < 100 || val > 300000 || val % 100 != 0)) {
		dev_err(dev, "idle_timeout: %u: invalid msecs specification; "
			"valid values are 0, 100-300000 in 100 increments\n",
			val);
		goto error_bad_value;
	}
	result = i2400m_set_idle_timeout(i2400m, val);
	if (result >= 0)
		result = size;
error_no_unsigned:
error_bad_value:
	return result;
}