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
typedef  int u32 ;
struct stu300_dev {TYPE_1__* pdev; int /*<<< orphan*/  cmd_err; scalar_t__ virtbase; } ;
typedef  enum stu300_event { ____Placeholder_stu300_event } stu300_event ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ I2C_SR1 ; 
 int I2C_SR1_ADD10_IND ; 
 int I2C_SR1_ADSL_IND ; 
 int I2C_SR1_BTF_IND ; 
 int I2C_SR1_EVF_IND ; 
 int I2C_SR1_SB_IND ; 
 scalar_t__ I2C_SR2 ; 
 int I2C_SR2_AF_IND ; 
 int I2C_SR2_ARLO_IND ; 
 int I2C_SR2_BERR_IND ; 
 int I2C_SR2_ENDAD_IND ; 
 int I2C_SR2_STOPF_IND ; 
 int /*<<< orphan*/  STU300_ERROR_ACKNOWLEDGE_FAILURE ; 
 int /*<<< orphan*/  STU300_ERROR_ARBITRATION_LOST ; 
 int /*<<< orphan*/  STU300_ERROR_BUS_ERROR ; 
 int /*<<< orphan*/  STU300_ERROR_UNKNOWN ; 
#define  STU300_EVENT_1 136 
#define  STU300_EVENT_2 135 
#define  STU300_EVENT_3 134 
#define  STU300_EVENT_4 133 
#define  STU300_EVENT_5 132 
#define  STU300_EVENT_6 131 
#define  STU300_EVENT_7 130 
#define  STU300_EVENT_8 129 
#define  STU300_EVENT_9 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  stu300_irq_disable (struct stu300_dev*) ; 
 int stu300_r8 (scalar_t__) ; 

__attribute__((used)) static int stu300_event_occurred(struct stu300_dev *dev,
				   enum stu300_event mr_event) {
	u32 status1;
	u32 status2;

	/* What event happened? */
	status1 = stu300_r8(dev->virtbase + I2C_SR1);

	if (!(status1 & I2C_SR1_EVF_IND))
		/* No event at all */
		return 0;

	status2 = stu300_r8(dev->virtbase + I2C_SR2);

	/* Block any multiple interrupts */
	stu300_irq_disable(dev);

	/* Check for errors first */
	if (status2 & I2C_SR2_AF_IND) {
		dev->cmd_err = STU300_ERROR_ACKNOWLEDGE_FAILURE;
		return 1;
	} else if (status2 & I2C_SR2_BERR_IND) {
		dev->cmd_err = STU300_ERROR_BUS_ERROR;
		return 1;
	} else if (status2 & I2C_SR2_ARLO_IND) {
		dev->cmd_err = STU300_ERROR_ARBITRATION_LOST;
		return 1;
	}

	switch (mr_event) {
	case STU300_EVENT_1:
		if (status1 & I2C_SR1_ADSL_IND)
			return 1;
		break;
	case STU300_EVENT_2:
	case STU300_EVENT_3:
	case STU300_EVENT_7:
	case STU300_EVENT_8:
		if (status1 & I2C_SR1_BTF_IND) {
			return 1;
		}
		break;
	case STU300_EVENT_4:
		if (status2 & I2C_SR2_STOPF_IND)
			return 1;
		break;
	case STU300_EVENT_5:
		if (status1 & I2C_SR1_SB_IND)
			/* Clear start bit */
			return 1;
		break;
	case STU300_EVENT_6:
		if (status2 & I2C_SR2_ENDAD_IND) {
			/* First check for any errors */
			return 1;
		}
		break;
	case STU300_EVENT_9:
		if (status1 & I2C_SR1_ADD10_IND)
			return 1;
		break;
	default:
		break;
	}
	/* If we get here, we're on thin ice.
	 * Here we are in a status where we have
	 * gotten a response that does not match
	 * what we requested.
	 */
	dev->cmd_err = STU300_ERROR_UNKNOWN;
	dev_err(&dev->pdev->dev,
		"Unhandled interrupt! %d sr1: 0x%x sr2: 0x%x\n",
		mr_event, status1, status2);
	return 0;
}