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
struct pmbus_data {int (* read_status ) (struct i2c_client*,int) ;} ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int PB_CML_FAULT_INVALID_COMMAND ; 
 int PB_STATUS_CML ; 
 int /*<<< orphan*/  PMBUS_STATUS_CML ; 
 int _pmbus_read_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 struct pmbus_data* i2c_get_clientdata (struct i2c_client*) ; 
 int stub1 (struct i2c_client*,int) ; 

__attribute__((used)) static int pmbus_check_status_cml(struct i2c_client *client)
{
	struct pmbus_data *data = i2c_get_clientdata(client);
	int status, status2;

	status = data->read_status(client, -1);
	if (status < 0 || (status & PB_STATUS_CML)) {
		status2 = _pmbus_read_byte_data(client, -1, PMBUS_STATUS_CML);
		if (status2 < 0 || (status2 & PB_CML_FAULT_INVALID_COMMAND))
			return -EIO;
	}
	return 0;
}