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
struct fsg_lun {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct fsg_lun* fsg_lun_from_dev (struct device*) ; 
 int /*<<< orphan*/  fsg_store_nofua (struct fsg_lun*,char const*,size_t) ; 

__attribute__((used)) static ssize_t nofua_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct fsg_lun		*curlun = fsg_lun_from_dev(dev);

	return fsg_store_nofua(curlun, buf, count);
}