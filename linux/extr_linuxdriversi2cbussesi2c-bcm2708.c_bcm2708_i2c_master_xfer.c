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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout; struct bcm2708_i2c* algo_data; } ;
struct bcm2708_i2c {int nmsgs; int error; int /*<<< orphan*/  lock; struct i2c_msg* msg; int /*<<< orphan*/  done; scalar_t__ pos; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  bcm2708_bsc_reset (struct bcm2708_i2c*) ; 
 int bcm2708_bsc_setup (struct bcm2708_i2c*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2708_i2c_master_xfer(struct i2c_adapter *adap,
	struct i2c_msg *msgs, int num)
{
	struct bcm2708_i2c *bi = adap->algo_data;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&bi->lock, flags);

	reinit_completion(&bi->done);
	bi->msg = msgs;
	bi->pos = 0;
	bi->nmsgs = num;
	bi->error = false;

	ret = bcm2708_bsc_setup(bi);

	spin_unlock_irqrestore(&bi->lock, flags);

	/* check the result of the setup */
	if (ret < 0)
	{
		dev_err(&adap->dev, "transfer setup timed out\n");
		goto error_timeout;
	}

	ret = wait_for_completion_timeout(&bi->done, adap->timeout);
	if (ret == 0) {
		dev_err(&adap->dev, "transfer timed out\n");
		goto error_timeout;
	}

	ret = bi->error ? -EIO : num;
	return ret;

error_timeout:
	spin_lock_irqsave(&bi->lock, flags);
	bcm2708_bsc_reset(bi);
	bi->msg = 0; /* to inform the interrupt handler that there's nothing else to be done */
	bi->nmsgs = 0;
	spin_unlock_irqrestore(&bi->lock, flags);
	return -ETIMEDOUT;
}