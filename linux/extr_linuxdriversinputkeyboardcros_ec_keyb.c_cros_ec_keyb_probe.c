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
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct cros_ec_keyb {struct device* dev; TYPE_1__ notifier; struct cros_ec_device* ec; } ;
struct cros_ec_device {int /*<<< orphan*/  event_notifier; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cros_ec_keyb_register_bs (struct cros_ec_keyb*) ; 
 int cros_ec_keyb_register_matrix (struct cros_ec_keyb*) ; 
 int /*<<< orphan*/  cros_ec_keyb_work ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct cros_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct cros_ec_keyb*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct cros_ec_keyb* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_ec_keyb_probe(struct platform_device *pdev)
{
	struct cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	struct device *dev = &pdev->dev;
	struct cros_ec_keyb *ckdev;
	int err;

	if (!dev->of_node)
		return -ENODEV;

	ckdev = devm_kzalloc(dev, sizeof(*ckdev), GFP_KERNEL);
	if (!ckdev)
		return -ENOMEM;

	ckdev->ec = ec;
	ckdev->dev = dev;
	dev_set_drvdata(dev, ckdev);

	err = cros_ec_keyb_register_matrix(ckdev);
	if (err) {
		dev_err(dev, "cannot register matrix inputs: %d\n", err);
		return err;
	}

	err = cros_ec_keyb_register_bs(ckdev);
	if (err) {
		dev_err(dev, "cannot register non-matrix inputs: %d\n", err);
		return err;
	}

	ckdev->notifier.notifier_call = cros_ec_keyb_work;
	err = blocking_notifier_chain_register(&ckdev->ec->event_notifier,
					       &ckdev->notifier);
	if (err) {
		dev_err(dev, "cannot register notifier: %d\n", err);
		return err;
	}

	device_init_wakeup(ckdev->dev, true);
	return 0;
}