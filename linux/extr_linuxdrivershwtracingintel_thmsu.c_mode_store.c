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
struct msc {int mode; int /*<<< orphan*/  buf_mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct msc* dev_get_drvdata (struct device*) ; 
 char* memchr (char const*,char,size_t) ; 
 int msc_buffer_unlocked_free_unless_used (struct msc*) ; 
 int /*<<< orphan*/ * msc_mode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static ssize_t
mode_store(struct device *dev, struct device_attribute *attr, const char *buf,
	   size_t size)
{
	struct msc *msc = dev_get_drvdata(dev);
	size_t len = size;
	char *cp;
	int i, ret;

	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;

	cp = memchr(buf, '\n', len);
	if (cp)
		len = cp - buf;

	for (i = 0; i < ARRAY_SIZE(msc_mode); i++)
		if (!strncmp(msc_mode[i], buf, len))
			goto found;

	return -EINVAL;

found:
	mutex_lock(&msc->buf_mutex);
	ret = msc_buffer_unlocked_free_unless_used(msc);
	if (!ret)
		msc->mode = i;
	mutex_unlock(&msc->buf_mutex);

	return ret ? ret : size;
}