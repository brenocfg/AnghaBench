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
struct cros_ec_device {int /*<<< orphan*/  event_notifier; } ;
struct cros_ec_dev {struct cros_ec_device* ec_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  notifier_call; } ;
struct cros_ec_cec {int /*<<< orphan*/  notify; int /*<<< orphan*/  adap; TYPE_6__ notifier; struct cros_ec_device* cros_ec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_CAP_DEFAULTS ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  cec_allocate_adapter (int /*<<< orphan*/ *,struct cros_ec_cec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 int cec_register_adapter (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cec_register_cec_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cros_ec_cec_event ; 
 int cros_ec_cec_get_notifier (TYPE_1__*,int /*<<< orphan*/ *) ; 
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
	int ret;

	cros_ec_cec = devm_kzalloc(&pdev->dev, sizeof(*cros_ec_cec),
				   GFP_KERNEL);
	if (!cros_ec_cec)
		return -ENOMEM;

	platform_set_drvdata(pdev, cros_ec_cec);
	cros_ec_cec->cros_ec = cros_ec;

	ret = cros_ec_cec_get_notifier(&pdev->dev, &cros_ec_cec->notify);
	if (ret)
		return ret;

	ret = device_init_wakeup(&pdev->dev, 1);
	if (ret) {
		dev_err(&pdev->dev, "failed to initialize wakeup\n");
		return ret;
	}

	cros_ec_cec->adap = cec_allocate_adapter(&cros_ec_cec_ops, cros_ec_cec,
						 DRV_NAME, CEC_CAP_DEFAULTS, 1);
	if (IS_ERR(cros_ec_cec->adap))
		return PTR_ERR(cros_ec_cec->adap);

	/* Get CEC events from the EC. */
	cros_ec_cec->notifier.notifier_call = cros_ec_cec_event;
	ret = blocking_notifier_chain_register(&cros_ec->event_notifier,
					       &cros_ec_cec->notifier);
	if (ret) {
		dev_err(&pdev->dev, "failed to register notifier\n");
		cec_delete_adapter(cros_ec_cec->adap);
		return ret;
	}

	ret = cec_register_adapter(cros_ec_cec->adap, &pdev->dev);
	if (ret < 0) {
		cec_delete_adapter(cros_ec_cec->adap);
		return ret;
	}

	cec_register_cec_notifier(cros_ec_cec->adap, cros_ec_cec->notify);

	return 0;
}