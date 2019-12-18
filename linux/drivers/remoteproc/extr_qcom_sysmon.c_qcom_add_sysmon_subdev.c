#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* parent; } ;
struct rproc {TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_7__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct qcom_sysmon {char const* name; int ssctl_instance; int shutdown_irq; int /*<<< orphan*/  node; TYPE_5__ nb; TYPE_2__ subdev; int /*<<< orphan*/  qmi; TYPE_3__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  shutdown_comp; int /*<<< orphan*/  ind_comp; int /*<<< orphan*/  comp; struct rproc* rproc; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOMEM ; 
 struct qcom_sysmon* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  SSCTL_MAX_MSG_LEN ; 
 int /*<<< orphan*/  blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct qcom_sysmon*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qcom_sysmon*) ; 
 struct qcom_sysmon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int of_irq_get_byname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qmi_add_lookup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qmi_handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmi_indication_handler ; 
 int /*<<< orphan*/  rproc_add_subdev (struct rproc*,TYPE_2__*) ; 
 int /*<<< orphan*/  ssctl_ops ; 
 int /*<<< orphan*/  sysmon_list ; 
 int /*<<< orphan*/  sysmon_lock ; 
 int /*<<< orphan*/  sysmon_notifiers ; 
 int /*<<< orphan*/  sysmon_notify ; 
 int /*<<< orphan*/  sysmon_shutdown_interrupt ; 
 int /*<<< orphan*/  sysmon_start ; 
 int /*<<< orphan*/  sysmon_stop ; 

struct qcom_sysmon *qcom_add_sysmon_subdev(struct rproc *rproc,
					   const char *name,
					   int ssctl_instance)
{
	struct qcom_sysmon *sysmon;
	int ret;

	sysmon = kzalloc(sizeof(*sysmon), GFP_KERNEL);
	if (!sysmon)
		return ERR_PTR(-ENOMEM);

	sysmon->dev = rproc->dev.parent;
	sysmon->rproc = rproc;

	sysmon->name = name;
	sysmon->ssctl_instance = ssctl_instance;

	init_completion(&sysmon->comp);
	init_completion(&sysmon->ind_comp);
	init_completion(&sysmon->shutdown_comp);
	mutex_init(&sysmon->lock);

	sysmon->shutdown_irq = of_irq_get_byname(sysmon->dev->of_node,
						 "shutdown-ack");
	if (sysmon->shutdown_irq < 0) {
		if (sysmon->shutdown_irq != -ENODATA) {
			dev_err(sysmon->dev,
				"failed to retrieve shutdown-ack IRQ\n");
			return ERR_PTR(sysmon->shutdown_irq);
		}
	} else {
		ret = devm_request_threaded_irq(sysmon->dev,
						sysmon->shutdown_irq,
						NULL, sysmon_shutdown_interrupt,
						IRQF_TRIGGER_RISING | IRQF_ONESHOT,
						"q6v5 shutdown-ack", sysmon);
		if (ret) {
			dev_err(sysmon->dev,
				"failed to acquire shutdown-ack IRQ\n");
			return ERR_PTR(ret);
		}
	}

	ret = qmi_handle_init(&sysmon->qmi, SSCTL_MAX_MSG_LEN, &ssctl_ops,
			      qmi_indication_handler);
	if (ret < 0) {
		dev_err(sysmon->dev, "failed to initialize qmi handle\n");
		kfree(sysmon);
		return ERR_PTR(ret);
	}

	qmi_add_lookup(&sysmon->qmi, 43, 0, 0);

	sysmon->subdev.start = sysmon_start;
	sysmon->subdev.stop = sysmon_stop;

	rproc_add_subdev(rproc, &sysmon->subdev);

	sysmon->nb.notifier_call = sysmon_notify;
	blocking_notifier_chain_register(&sysmon_notifiers, &sysmon->nb);

	mutex_lock(&sysmon_lock);
	list_add(&sysmon->node, &sysmon_list);
	mutex_unlock(&sysmon_lock);

	return sysmon;
}