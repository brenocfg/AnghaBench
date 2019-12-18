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
struct TYPE_4__ {unsigned int ack; } ;
union pvrdma_cmd_resp {TYPE_2__ hdr; } ;
struct pvrdma_dev {TYPE_1__* pdev; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  resp_slot; int /*<<< orphan*/  cmd_done; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PVRDMA_CMD_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (union pvrdma_cmd_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pvrdma_cmd_recv(struct pvrdma_dev *dev,
				  union pvrdma_cmd_resp *resp,
				  unsigned resp_code)
{
	int err;

	dev_dbg(&dev->pdev->dev, "receive response from device\n");

	err = wait_for_completion_interruptible_timeout(&dev->cmd_done,
			msecs_to_jiffies(PVRDMA_CMD_TIMEOUT));
	if (err == 0 || err == -ERESTARTSYS) {
		dev_warn(&dev->pdev->dev,
			 "completion timeout or interrupted\n");
		return -ETIMEDOUT;
	}

	spin_lock(&dev->cmd_lock);
	memcpy(resp, dev->resp_slot, sizeof(*resp));
	spin_unlock(&dev->cmd_lock);

	if (resp->hdr.ack != resp_code) {
		dev_warn(&dev->pdev->dev,
			 "unknown response %#x expected %#x\n",
			 resp->hdr.ack, resp_code);
		return -EFAULT;
	}

	return 0;
}