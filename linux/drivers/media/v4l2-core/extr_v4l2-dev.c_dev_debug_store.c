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
typedef  int /*<<< orphan*/  u16 ;
struct video_device {int /*<<< orphan*/  dev_debug; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct video_device* to_video_device (struct device*) ; 

__attribute__((used)) static ssize_t dev_debug_store(struct device *cd, struct device_attribute *attr,
			  const char *buf, size_t len)
{
	struct video_device *vdev = to_video_device(cd);
	int res = 0;
	u16 value;

	res = kstrtou16(buf, 0, &value);
	if (res)
		return res;

	vdev->dev_debug = value;
	return len;
}