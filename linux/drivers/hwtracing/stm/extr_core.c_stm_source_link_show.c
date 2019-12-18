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
struct stm_source_device {int /*<<< orphan*/  link; } ;
struct stm_device {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,char*) ; 
 struct stm_device* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stm_source_srcu ; 
 struct stm_source_device* to_stm_source_device (struct device*) ; 

__attribute__((used)) static ssize_t stm_source_link_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct stm_source_device *src = to_stm_source_device(dev);
	struct stm_device *stm;
	int idx, ret;

	idx = srcu_read_lock(&stm_source_srcu);
	stm = srcu_dereference(src->link, &stm_source_srcu);
	ret = sprintf(buf, "%s\n",
		      stm ? dev_name(&stm->dev) : "<none>");
	srcu_read_unlock(&stm_source_srcu, idx);

	return ret;
}