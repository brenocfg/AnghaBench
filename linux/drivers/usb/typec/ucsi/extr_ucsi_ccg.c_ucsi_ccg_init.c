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
typedef  int /*<<< orphan*/  u8 ;
struct ucsi_ccg {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_INTR_REG ; 
 int /*<<< orphan*/  CCGX_RAB_UCSI_CONTROL ; 
 int /*<<< orphan*/  CCGX_RAB_UCSI_CONTROL_START ; 
 int /*<<< orphan*/  CCGX_RAB_UCSI_CONTROL_STOP ; 
 int ETIMEDOUT ; 
 int ccg_read (struct ucsi_ccg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ccg_write (struct ucsi_ccg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ucsi_ccg_init(struct ucsi_ccg *uc)
{
	unsigned int count = 10;
	u8 data;
	int status;

	data = CCGX_RAB_UCSI_CONTROL_STOP;
	status = ccg_write(uc, CCGX_RAB_UCSI_CONTROL, &data, sizeof(data));
	if (status < 0)
		return status;

	data = CCGX_RAB_UCSI_CONTROL_START;
	status = ccg_write(uc, CCGX_RAB_UCSI_CONTROL, &data, sizeof(data));
	if (status < 0)
		return status;

	/*
	 * Flush CCGx RESPONSE queue by acking interrupts. Above ucsi control
	 * register write will push response which must be cleared.
	 */
	do {
		status = ccg_read(uc, CCGX_RAB_INTR_REG, &data, sizeof(data));
		if (status < 0)
			return status;

		if (!data)
			return 0;

		status = ccg_write(uc, CCGX_RAB_INTR_REG, &data, sizeof(data));
		if (status < 0)
			return status;

		usleep_range(10000, 11000);
	} while (--count);

	return -ETIMEDOUT;
}