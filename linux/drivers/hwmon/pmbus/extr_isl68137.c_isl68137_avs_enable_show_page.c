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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ISL68137_VOUT_AVS ; 
 int /*<<< orphan*/  PMBUS_OPERATION ; 
 int pmbus_read_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t isl68137_avs_enable_show_page(struct i2c_client *client,
					     int page,
					     char *buf)
{
	int val = pmbus_read_byte_data(client, page, PMBUS_OPERATION);

	return sprintf(buf, "%d\n",
		       (val & ISL68137_VOUT_AVS) == ISL68137_VOUT_AVS ? 1 : 0);
}