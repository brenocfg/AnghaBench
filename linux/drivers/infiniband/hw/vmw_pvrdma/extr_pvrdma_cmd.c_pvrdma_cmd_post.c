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
typedef  union pvrdma_cmd_resp {int dummy; } pvrdma_cmd_resp ;
typedef  union pvrdma_cmd_req {int dummy; } pvrdma_cmd_req ;
struct pvrdma_dev {int /*<<< orphan*/  cmd_sema; TYPE_1__* pdev; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  cmd_slot; } ;
struct pvrdma_cmd_modify_qp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFAULT ; 
 int /*<<< orphan*/  PVRDMA_REG_ERR ; 
 int /*<<< orphan*/  PVRDMA_REG_REQUEST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,union pvrdma_cmd_req*,int) ; 
 int pvrdma_cmd_recv (struct pvrdma_dev*,union pvrdma_cmd_resp*,unsigned int) ; 
 int pvrdma_read_reg (struct pvrdma_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_write_reg (struct pvrdma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int
pvrdma_cmd_post(struct pvrdma_dev *dev, union pvrdma_cmd_req *req,
		union pvrdma_cmd_resp *resp, unsigned resp_code)
{
	int err;

	dev_dbg(&dev->pdev->dev, "post request to device\n");

	/* Serializiation */
	down(&dev->cmd_sema);

	BUILD_BUG_ON(sizeof(union pvrdma_cmd_req) !=
		     sizeof(struct pvrdma_cmd_modify_qp));

	spin_lock(&dev->cmd_lock);
	memcpy(dev->cmd_slot, req, sizeof(*req));
	spin_unlock(&dev->cmd_lock);

	init_completion(&dev->cmd_done);
	pvrdma_write_reg(dev, PVRDMA_REG_REQUEST, 0);

	/* Make sure the request is written before reading status. */
	mb();

	err = pvrdma_read_reg(dev, PVRDMA_REG_ERR);
	if (err == 0) {
		if (resp != NULL)
			err = pvrdma_cmd_recv(dev, resp, resp_code);
	} else {
		dev_warn(&dev->pdev->dev,
			 "failed to write request error reg: %d\n", err);
		err = -EFAULT;
	}

	up(&dev->cmd_sema);

	return err;
}