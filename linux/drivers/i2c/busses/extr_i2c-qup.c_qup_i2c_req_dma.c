#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dma; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dma; } ;
struct qup_i2c_dev {TYPE_2__ brx; int /*<<< orphan*/  dev; TYPE_1__ btx; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dma_request_slave_channel_reason (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qup_i2c_rel_dma (struct qup_i2c_dev*) ; 

__attribute__((used)) static int qup_i2c_req_dma(struct qup_i2c_dev *qup)
{
	int err;

	if (!qup->btx.dma) {
		qup->btx.dma = dma_request_slave_channel_reason(qup->dev, "tx");
		if (IS_ERR(qup->btx.dma)) {
			err = PTR_ERR(qup->btx.dma);
			qup->btx.dma = NULL;
			dev_err(qup->dev, "\n tx channel not available");
			return err;
		}
	}

	if (!qup->brx.dma) {
		qup->brx.dma = dma_request_slave_channel_reason(qup->dev, "rx");
		if (IS_ERR(qup->brx.dma)) {
			dev_err(qup->dev, "\n rx channel not available");
			err = PTR_ERR(qup->brx.dma);
			qup->brx.dma = NULL;
			qup_i2c_rel_dma(qup);
			return err;
		}
	}
	return 0;
}