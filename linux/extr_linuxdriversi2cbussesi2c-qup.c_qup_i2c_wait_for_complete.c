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
struct qup_i2c_dev {int bus_err; scalar_t__ qup_err; scalar_t__ base; int /*<<< orphan*/  xfer_timeout; int /*<<< orphan*/  xfer; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int QUP_I2C_NACK_FLAG ; 
 scalar_t__ QUP_SW_RESET ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int qup_i2c_wait_for_complete(struct qup_i2c_dev *qup,
				     struct i2c_msg *msg)
{
	unsigned long left;
	int ret = 0;

	left = wait_for_completion_timeout(&qup->xfer, qup->xfer_timeout);
	if (!left) {
		writel(1, qup->base + QUP_SW_RESET);
		ret = -ETIMEDOUT;
	}

	if (qup->bus_err || qup->qup_err)
		ret =  (qup->bus_err & QUP_I2C_NACK_FLAG) ? -ENXIO : -EIO;

	return ret;
}