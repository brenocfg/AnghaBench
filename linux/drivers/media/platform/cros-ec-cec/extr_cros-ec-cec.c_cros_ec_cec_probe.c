#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct cros_ec_device {int /*<<< orphan*/  event_notifier; } ;
struct cros_ec_dev {struct cros_ec_device* ec_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  notifier_call; } ;
struct cros_ec_cec {struct device* adap; int /*<<< orphan*/  notify; TYPE_6__ notifier; struct cros_ec_device* cros_ec; } ;

/* Variables and functions */
 int CEC_CAP_CONNECTOR_INFO ; 
 int CEC_CAP_DEFAULTS ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_6__*) ; 
 struct device* cec_allocate_adapter (int /*<<< orphan*/ *,struct cros_ec_cec*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cec_delete_adapter (struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_register (struct device*,char const*,struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 int cec_register_adapter (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  cros_ec_cec_event ; 
 struct device* cros_ec_cec_find_hdmi_dev (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  cros_ec_cec_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int device_init_wakeup (TYPE_1__*,int) ; 
 struct cros_ec_cec* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cros_ec_cec*) ; 

__attribute__((used)) static int cros_ec_cec_probe(struct platform_device *pdev)
{
	struct cros_ec_dev *ec_dev = dev_get_drvdata(pdev->dev.parent);
	struct cros_ec_device *cros_ec = ec_dev->ec_dev;
	struct cros_ec_cec *cros_ec_cec;
	struct device *hdmi_dev;
	const char *conn = NULL;
	int ret;

	hdmi_dev = cros_ec_cec_find_hdmi_dev(&pdev->dev, &conn);
	if (IS_ERR(hdmi_dev))
		return PTR_ERR(hdmi_dev);

	cros_ec_cec = devm_kzalloc(&pdev->dev, sizeof(*cros_ec_cec),
				   GFP_KERNEL);
	if (!cros_ec_cec)
		return -ENOMEM;

	platform_set_drvdata(pdev, cros_ec_cec);
	cros_ec_cec->cros_ec = cros_ec;

	ret = device_init_wakeup(&pdev->dev, 1);
	if (ret) {
		dev_err(&pdev->dev, "failed to initialize wakeup\n");
		return ret;
	}

	cros_ec_cec->adap = cec_allocate_adapter(&cros_ec_cec_ops, cros_ec_cec,
						 DRV_NAME,
						 CEC_CAP_DEFAULTS |
						 CEC_CAP_CONNECTOR_INFO, 1);
	if (IS_ERR(cros_ec_cec->adap))
		return PTR_ERR(cros_ec_cec->adap);

	cros_ec_cec->notify = cec_notifier_cec_adap_register(hdmi_dev, conn,
							     cros_ec_cec->adap);
	if (!cros_ec_cec->notify) {
		ret = -ENOMEM;
		goto out_probe_adapter;
	}

	/* Get CEC events from the EC. */
	cros_ec_cec->notifier.notifier_call = cros_ec_cec_event;
	ret = blocking_notifier_chain_register(&cros_ec->event_notifier,
					       &cros_ec_cec->notifier);
	if (ret) {
		dev_err(&pdev->dev, "failed to register notifier\n");
		goto out_probe_notify;
	}

	ret = cec_register_adapter(cros_ec_cec->adap, &pdev->dev);
	if (ret < 0)
		goto out_probe_notify;

	return 0;

out_probe_notify:
	cec_notifier_cec_adap_unregister(cros_ec_cec->notify);
out_probe_adapter:
	cec_delete_adapter(cros_ec_cec->adap);
	return ret;
}