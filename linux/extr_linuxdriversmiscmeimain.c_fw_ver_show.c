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
struct mei_fw_version {int /*<<< orphan*/  buildno; int /*<<< orphan*/  hotfix; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  platform; } ;
struct mei_device {struct mei_fw_version* fw_ver; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int MEI_MAX_FW_VER_BLOCKS ; 
 int PAGE_SIZE ; 
 struct mei_device* dev_get_drvdata (struct device*) ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fw_ver_show(struct device *device,
			   struct device_attribute *attr, char *buf)
{
	struct mei_device *dev = dev_get_drvdata(device);
	struct mei_fw_version *ver;
	ssize_t cnt = 0;
	int i;

	ver = dev->fw_ver;

	for (i = 0; i < MEI_MAX_FW_VER_BLOCKS; i++)
		cnt += scnprintf(buf + cnt, PAGE_SIZE - cnt, "%u:%u.%u.%u.%u\n",
				 ver[i].platform, ver[i].major, ver[i].minor,
				 ver[i].hotfix, ver[i].buildno);
	return cnt;
}