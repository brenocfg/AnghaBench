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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct cros_ec_cec {int /*<<< orphan*/  adap; int /*<<< orphan*/  notify; int /*<<< orphan*/  notifier; TYPE_1__* cros_ec; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_notifier; } ;

/* Variables and functions */
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct cros_ec_cec* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cros_ec_cec_remove(struct platform_device *pdev)
{
	struct cros_ec_cec *cros_ec_cec = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	int ret;

	ret = blocking_notifier_chain_unregister(
			&cros_ec_cec->cros_ec->event_notifier,
			&cros_ec_cec->notifier);

	if (ret) {
		dev_err(dev, "failed to unregister notifier\n");
		return ret;
	}

	cec_notifier_cec_adap_unregister(cros_ec_cec->notify);
	cec_unregister_adapter(cros_ec_cec->adap);

	return 0;
}