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
struct i2c_client {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ISL68137_VOUT_AVS ; 
 int /*<<< orphan*/  PMBUS_OPERATION ; 
 int /*<<< orphan*/  PMBUS_VOUT_COMMAND ; 
 int kstrtobool (char const*,int*) ; 
 int pmbus_read_word_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int pmbus_update_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ,int,int) ; 
 int pmbus_write_word_data (struct i2c_client*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t isl68137_avs_enable_store_page(struct i2c_client *client,
					      int page,
					      const char *buf, size_t count)
{
	int rc, op_val;
	bool result;

	rc = kstrtobool(buf, &result);
	if (rc)
		return rc;

	op_val = result ? ISL68137_VOUT_AVS : 0;

	/*
	 * Writes to VOUT setpoint over AVSBus will persist after the VRM is
	 * switched to PMBus control. Switching back to AVSBus control
	 * restores this persisted setpoint rather than re-initializing to
	 * PMBus VOUT_COMMAND. Writing VOUT_COMMAND first over PMBus before
	 * enabling AVS control is the workaround.
	 */
	if (op_val == ISL68137_VOUT_AVS) {
		rc = pmbus_read_word_data(client, page, PMBUS_VOUT_COMMAND);
		if (rc < 0)
			return rc;

		rc = pmbus_write_word_data(client, page, PMBUS_VOUT_COMMAND,
					   rc);
		if (rc < 0)
			return rc;
	}

	rc = pmbus_update_byte_data(client, page, PMBUS_OPERATION,
				    ISL68137_VOUT_AVS, op_val);

	return (rc < 0) ? rc : count;
}