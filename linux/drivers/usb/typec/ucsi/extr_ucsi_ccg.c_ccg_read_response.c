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
typedef  int u8 ;
struct ucsi_ccg {int /*<<< orphan*/  dev_resp; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  intval ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_INTR_REG ; 
 int /*<<< orphan*/  CCGX_RAB_RESPONSE ; 
 int DEV_INT ; 
 int ETIME ; 
 int ccg_read (struct ucsi_ccg*,int /*<<< orphan*/ ,int*,int) ; 
 int ccg_write (struct ucsi_ccg*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ccg_read_response(struct ucsi_ccg *uc)
{
	unsigned long target = jiffies + msecs_to_jiffies(1000);
	struct device *dev = uc->dev;
	u8 intval;
	int status;

	/* wait for interrupt status to get updated */
	do {
		status = ccg_read(uc, CCGX_RAB_INTR_REG, &intval,
				  sizeof(intval));
		if (status < 0)
			return status;

		if (intval & DEV_INT)
			break;
		usleep_range(500, 600);
	} while (time_is_after_jiffies(target));

	if (time_is_before_jiffies(target)) {
		dev_err(dev, "response timeout error\n");
		return -ETIME;
	}

	status = ccg_read(uc, CCGX_RAB_RESPONSE, (u8 *)&uc->dev_resp,
			  sizeof(uc->dev_resp));
	if (status < 0)
		return status;

	status = ccg_write(uc, CCGX_RAB_INTR_REG, &intval, sizeof(intval));
	if (status < 0)
		return status;

	return 0;
}