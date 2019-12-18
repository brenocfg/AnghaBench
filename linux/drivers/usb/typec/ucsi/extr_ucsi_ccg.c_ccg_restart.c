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
struct ucsi_ccg {int /*<<< orphan*/  ucsi; struct device* dev; int /*<<< orphan*/  ppm; int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccg_irq_handler ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ucsi_ccg*) ; 
 int ucsi_ccg_init (struct ucsi_ccg*) ; 
 int /*<<< orphan*/  ucsi_register_ppm (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccg_restart(struct ucsi_ccg *uc)
{
	struct device *dev = uc->dev;
	int status;

	status = ucsi_ccg_init(uc);
	if (status < 0) {
		dev_err(dev, "ucsi_ccg_start fail, err=%d\n", status);
		return status;
	}

	status = request_threaded_irq(uc->irq, NULL, ccg_irq_handler,
				      IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
				      dev_name(dev), uc);
	if (status < 0) {
		dev_err(dev, "request_threaded_irq failed - %d\n", status);
		return status;
	}

	uc->ucsi = ucsi_register_ppm(dev, &uc->ppm);
	if (IS_ERR(uc->ucsi)) {
		dev_err(uc->dev, "ucsi_register_ppm failed\n");
		return PTR_ERR(uc->ucsi);
	}

	return 0;
}