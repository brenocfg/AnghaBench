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
typedef  int u32 ;
struct hwq {int /*<<< orphan*/  irqpoll; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxlflash_cfg {struct afu* afu; TYPE_1__* dev; } ;
struct afu {int irqpoll_weight; int num_hwqs; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ afu_is_irqpoll_enabled (struct afu*) ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  cxlflash_irqpoll ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct hwq* get_hwq (struct afu*,int) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_poll_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int kstrtouint (char const*,int,int*) ; 
 struct cxlflash_cfg* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t irqpoll_weight_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	struct device *cfgdev = &cfg->dev->dev;
	struct afu *afu = cfg->afu;
	struct hwq *hwq;
	u32 weight;
	int rc, i;

	rc = kstrtouint(buf, 10, &weight);
	if (rc)
		return -EINVAL;

	if (weight > 256) {
		dev_info(cfgdev,
			 "Invalid IRQ poll weight. It must be 256 or less.\n");
		return -EINVAL;
	}

	if (weight == afu->irqpoll_weight) {
		dev_info(cfgdev,
			 "Current IRQ poll weight has the same weight.\n");
		return -EINVAL;
	}

	if (afu_is_irqpoll_enabled(afu)) {
		for (i = 0; i < afu->num_hwqs; i++) {
			hwq = get_hwq(afu, i);

			irq_poll_disable(&hwq->irqpoll);
		}
	}

	afu->irqpoll_weight = weight;

	if (weight > 0) {
		for (i = 0; i < afu->num_hwqs; i++) {
			hwq = get_hwq(afu, i);

			irq_poll_init(&hwq->irqpoll, weight, cxlflash_irqpoll);
		}
	}

	return count;
}