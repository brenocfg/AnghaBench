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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DK_CXLFLASH_VERSION_0 ; 
 int /*<<< orphan*/  HT_CXLFLASH_VERSION_0 ; 
 int PAGE_SIZE ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ioctl_version_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	ssize_t bytes = 0;

	bytes = scnprintf(buf, PAGE_SIZE,
			  "disk: %u\n", DK_CXLFLASH_VERSION_0);
	bytes += scnprintf(buf + bytes, PAGE_SIZE - bytes,
			   "host: %u\n", HT_CXLFLASH_VERSION_0);

	return bytes;
}