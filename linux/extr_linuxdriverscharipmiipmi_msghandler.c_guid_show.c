#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bmc_device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ guid_t ;

/* Variables and functions */
 int ENOENT ; 
 int bmc_get_device_id (int /*<<< orphan*/ *,struct bmc_device*,int /*<<< orphan*/ *,int*,TYPE_1__*) ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 struct bmc_device* to_bmc_device (struct device*) ; 

__attribute__((used)) static ssize_t guid_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct bmc_device *bmc = to_bmc_device(dev);
	bool guid_set;
	guid_t guid;
	int rv;

	rv = bmc_get_device_id(NULL, bmc, NULL, &guid_set, &guid);
	if (rv)
		return rv;
	if (!guid_set)
		return -ENOENT;

	return snprintf(buf, 38, "%pUl\n", guid.b);
}