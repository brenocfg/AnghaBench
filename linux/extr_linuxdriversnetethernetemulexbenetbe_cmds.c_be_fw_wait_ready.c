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
typedef  int u16 ;
struct device {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int EINTR ; 
 int ETIMEDOUT ; 
 int POST_STAGE_ARMFW_RDY ; 
 int be_POST_stage_get (struct be_adapter*) ; 
 scalar_t__ be_virtfn (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int lancer_wait_ready (struct be_adapter*) ; 
 scalar_t__ msleep_interruptible (int) ; 

int be_fw_wait_ready(struct be_adapter *adapter)
{
	u16 stage;
	int status, timeout = 0;
	struct device *dev = &adapter->pdev->dev;

	if (lancer_chip(adapter)) {
		status = lancer_wait_ready(adapter);
		if (status) {
			stage = status;
			goto err;
		}
		return 0;
	}

	do {
		/* There's no means to poll POST state on BE2/3 VFs */
		if (BEx_chip(adapter) && be_virtfn(adapter))
			return 0;

		stage = be_POST_stage_get(adapter);
		if (stage == POST_STAGE_ARMFW_RDY)
			return 0;

		dev_info(dev, "Waiting for POST, %ds elapsed\n", timeout);
		if (msleep_interruptible(2000)) {
			dev_err(dev, "Waiting for POST aborted\n");
			return -EINTR;
		}
		timeout += 2;
	} while (timeout < 60);

err:
	dev_err(dev, "POST timeout; stage=%#x\n", stage);
	return -ETIMEDOUT;
}