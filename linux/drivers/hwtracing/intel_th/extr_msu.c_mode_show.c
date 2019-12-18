#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msc {size_t mode; int /*<<< orphan*/  buf_mutex; TYPE_1__* mbuf; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct msc* dev_get_drvdata (struct device*) ; 
 char** msc_mode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static ssize_t
mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct msc *msc = dev_get_drvdata(dev);
	const char *mode = msc_mode[msc->mode];
	ssize_t ret;

	mutex_lock(&msc->buf_mutex);
	if (msc->mbuf)
		mode = msc->mbuf->name;
	ret = scnprintf(buf, PAGE_SIZE, "%s\n", mode);
	mutex_unlock(&msc->buf_mutex);

	return ret;
}