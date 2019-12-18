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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPACPI_RFK_WWAN_SW_ID ; 
 int /*<<< orphan*/  tpacpi_rfk_sysfs_enable_store (int /*<<< orphan*/ ,struct device_attribute*,char const*,size_t) ; 

__attribute__((used)) static ssize_t wan_enable_store(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf, size_t count)
{
	return tpacpi_rfk_sysfs_enable_store(TPACPI_RFK_WWAN_SW_ID,
			attr, buf, count);
}