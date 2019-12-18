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
typedef  unsigned int u8 ;
struct rc_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned int BUF_PULSE_BIT ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int /*<<< orphan*/ ) ; 
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SAMPLE_PERIOD ; 
 int WAKEUP_MAX_SIZE ; 
 int /*<<< orphan*/  argv_free (char**) ; 
 char** argv_split (int /*<<< orphan*/ ,char const*,int*) ; 
 size_t kstrtouint (char*,int,unsigned int*) ; 
 int /*<<< orphan*/  nvt_write_wakeup_codes (struct rc_dev*,unsigned int*,int) ; 
 struct rc_dev* to_rc_dev (struct device*) ; 

__attribute__((used)) static ssize_t wakeup_data_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t len)
{
	struct rc_dev *rc_dev = to_rc_dev(dev);
	u8 wake_buf[WAKEUP_MAX_SIZE];
	char **argv;
	int i, count;
	unsigned int val;
	ssize_t ret;

	argv = argv_split(GFP_KERNEL, buf, &count);
	if (!argv)
		return -ENOMEM;
	if (!count || count > WAKEUP_MAX_SIZE) {
		ret = -EINVAL;
		goto out;
	}

	for (i = 0; i < count; i++) {
		ret = kstrtouint(argv[i], 10, &val);
		if (ret)
			goto out;
		val = DIV_ROUND_CLOSEST(val, SAMPLE_PERIOD);
		if (!val || val > 0x7f) {
			ret = -EINVAL;
			goto out;
		}
		wake_buf[i] = val;
		/* sequence must start with a pulse */
		if (i % 2 == 0)
			wake_buf[i] |= BUF_PULSE_BIT;
	}

	nvt_write_wakeup_codes(rc_dev, wake_buf, count);

	ret = len;
out:
	argv_free(argv);
	return ret;
}