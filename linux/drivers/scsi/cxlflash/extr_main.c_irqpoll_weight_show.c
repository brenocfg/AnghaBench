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
struct cxlflash_cfg {struct afu* afu; } ;
struct afu {int /*<<< orphan*/  irqpoll_weight; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct cxlflash_cfg* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t irqpoll_weight_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	struct afu *afu = cfg->afu;

	return scnprintf(buf, PAGE_SIZE, "%u\n", afu->irqpoll_weight);
}