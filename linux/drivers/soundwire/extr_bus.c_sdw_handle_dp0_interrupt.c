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
typedef  int u8 ;
struct sdw_slave {TYPE_1__* bus; int /*<<< orphan*/  dev; int /*<<< orphan*/ * port_ready; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDW_DP0_INT ; 
 int SDW_DP0_INT_BRA_FAILURE ; 
 int SDW_DP0_INT_IMPDEF1 ; 
 int SDW_DP0_INT_IMPDEF2 ; 
 int SDW_DP0_INT_IMPDEF3 ; 
 int SDW_DP0_INT_PORT_READY ; 
 int SDW_DP0_INT_TEST_FAIL ; 
 int SDW_READ_INTR_CLEAR_RETRY ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int sdw_read (struct sdw_slave*,int /*<<< orphan*/ ) ; 
 int sdw_write (struct sdw_slave*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdw_handle_dp0_interrupt(struct sdw_slave *slave, u8 *slave_status)
{
	u8 clear = 0, impl_int_mask;
	int status, status2, ret, count = 0;

	status = sdw_read(slave, SDW_DP0_INT);
	if (status < 0) {
		dev_err(slave->bus->dev,
			"SDW_DP0_INT read failed:%d\n", status);
		return status;
	}

	do {
		if (status & SDW_DP0_INT_TEST_FAIL) {
			dev_err(&slave->dev, "Test fail for port 0\n");
			clear |= SDW_DP0_INT_TEST_FAIL;
		}

		/*
		 * Assumption: PORT_READY interrupt will be received only for
		 * ports implementing Channel Prepare state machine (CP_SM)
		 */

		if (status & SDW_DP0_INT_PORT_READY) {
			complete(&slave->port_ready[0]);
			clear |= SDW_DP0_INT_PORT_READY;
		}

		if (status & SDW_DP0_INT_BRA_FAILURE) {
			dev_err(&slave->dev, "BRA failed\n");
			clear |= SDW_DP0_INT_BRA_FAILURE;
		}

		impl_int_mask = SDW_DP0_INT_IMPDEF1 |
			SDW_DP0_INT_IMPDEF2 | SDW_DP0_INT_IMPDEF3;

		if (status & impl_int_mask) {
			clear |= impl_int_mask;
			*slave_status = clear;
		}

		/* clear the interrupt */
		ret = sdw_write(slave, SDW_DP0_INT, clear);
		if (ret < 0) {
			dev_err(slave->bus->dev,
				"SDW_DP0_INT write failed:%d\n", ret);
			return ret;
		}

		/* Read DP0 interrupt again */
		status2 = sdw_read(slave, SDW_DP0_INT);
		if (status2 < 0) {
			dev_err(slave->bus->dev,
				"SDW_DP0_INT read failed:%d\n", status2);
			return status2;
		}
		status &= status2;

		count++;

		/* we can get alerts while processing so keep retrying */
	} while (status != 0 && count < SDW_READ_INTR_CLEAR_RETRY);

	if (count == SDW_READ_INTR_CLEAR_RETRY)
		dev_warn(slave->bus->dev, "Reached MAX_RETRY on DP0 read\n");

	return ret;
}