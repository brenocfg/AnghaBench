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
struct device_driver {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ccwgroup_create_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lcs_group_driver ; 
 int /*<<< orphan*/  lcs_root_dev ; 

__attribute__((used)) static ssize_t group_store(struct device_driver *ddrv, const char *buf,
			   size_t count)
{
	int err;
	err = ccwgroup_create_dev(lcs_root_dev, &lcs_group_driver, 2, buf);
	return err ? err : count;
}