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
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_MAX_BASELINE_CMD ; 
 int /*<<< orphan*/  ETP_I2C_MIN_BASELINE_CMD ; 
 int elan_i2c_read_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_i2c_get_baseline_data(struct i2c_client *client,
				      bool max_baseline, u8 *value)
{
	int error;
	u8 val[3];

	error = elan_i2c_read_cmd(client,
				  max_baseline ? ETP_I2C_MAX_BASELINE_CMD :
						 ETP_I2C_MIN_BASELINE_CMD,
				  val);
	if (error)
		return error;

	*value = le16_to_cpup((__le16 *)val);

	return 0;
}