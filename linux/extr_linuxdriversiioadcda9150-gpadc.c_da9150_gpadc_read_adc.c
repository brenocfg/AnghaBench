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
struct da9150_gpadc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  da9150; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int DA9150_GPADC_EN_MASK ; 
 int /*<<< orphan*/  DA9150_GPADC_MAN ; 
 int DA9150_GPADC_MUX_SHIFT ; 
 int /*<<< orphan*/  DA9150_GPADC_RES_A ; 
 int DA9150_GPADC_RES_L_BITS ; 
 int DA9150_GPADC_RES_L_MASK ; 
 int DA9150_GPADC_RES_L_SHIFT ; 
 int DA9150_GPADC_RUN_MASK ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  da9150_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  da9150_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_gpadc_read_adc(struct da9150_gpadc *gpadc, int hw_chan)
{
	u8 result_regs[2];
	int result;

	mutex_lock(&gpadc->lock);

	/* Set channel & enable measurement */
	da9150_reg_write(gpadc->da9150, DA9150_GPADC_MAN,
			 (DA9150_GPADC_EN_MASK |
			  hw_chan << DA9150_GPADC_MUX_SHIFT));

	/* Consume left-over completion from a previous timeout */
	try_wait_for_completion(&gpadc->complete);

	/* Check for actual completion */
	wait_for_completion_timeout(&gpadc->complete, msecs_to_jiffies(5));

	/* Read result and status from device */
	da9150_bulk_read(gpadc->da9150, DA9150_GPADC_RES_A, 2, result_regs);

	mutex_unlock(&gpadc->lock);

	/* Check to make sure device really has completed reading */
	if (result_regs[1] & DA9150_GPADC_RUN_MASK) {
		dev_err(gpadc->dev, "Timeout on channel %d of GPADC\n",
			hw_chan);
		return -ETIMEDOUT;
	}

	/* LSBs - 2 bits */
	result = (result_regs[1] & DA9150_GPADC_RES_L_MASK) >>
		 DA9150_GPADC_RES_L_SHIFT;
	/* MSBs - 8 bits */
	result |= result_regs[0] << DA9150_GPADC_RES_L_BITS;

	return result;
}