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
struct notifier_block {int /*<<< orphan*/  notifier_call; } ;
struct device {int dummy; } ;
struct devfreq_passive_data {struct devfreq* this; struct notifier_block nb; scalar_t__ parent; } ;
struct TYPE_2__ {struct device* parent; } ;
struct devfreq {scalar_t__ data; TYPE_1__ dev; } ;

/* Variables and functions */
#define  DEVFREQ_GOV_START 129 
#define  DEVFREQ_GOV_STOP 128 
 int /*<<< orphan*/  DEVFREQ_TRANSITION_NOTIFIER ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  devfreq_passive_notifier_call ; 
 int devm_devfreq_register_notifier (struct device*,struct devfreq*,struct notifier_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_devfreq_unregister_notifier (struct device*,struct devfreq*,struct notifier_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devfreq_passive_event_handler(struct devfreq *devfreq,
				unsigned int event, void *data)
{
	struct device *dev = devfreq->dev.parent;
	struct devfreq_passive_data *p_data
			= (struct devfreq_passive_data *)devfreq->data;
	struct devfreq *parent = (struct devfreq *)p_data->parent;
	struct notifier_block *nb = &p_data->nb;
	int ret = 0;

	if (!parent)
		return -EPROBE_DEFER;

	switch (event) {
	case DEVFREQ_GOV_START:
		if (!p_data->this)
			p_data->this = devfreq;

		nb->notifier_call = devfreq_passive_notifier_call;
		ret = devm_devfreq_register_notifier(dev, parent, nb,
					DEVFREQ_TRANSITION_NOTIFIER);
		break;
	case DEVFREQ_GOV_STOP:
		devm_devfreq_unregister_notifier(dev, parent, nb,
					DEVFREQ_TRANSITION_NOTIFIER);
		break;
	default:
		break;
	}

	return ret;
}