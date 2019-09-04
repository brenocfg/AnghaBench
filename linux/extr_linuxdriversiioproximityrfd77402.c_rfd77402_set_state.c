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
typedef  int u16 ;
struct rfd77402_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RFD77402_CMD_R ; 
 int RFD77402_CMD_VALID ; 
 int RFD77402_STATUS_PM_MASK ; 
 int /*<<< orphan*/  RFD77402_STATUS_R ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rfd77402_set_state(struct rfd77402_data *data, u8 state, u16 check)
{
	int ret;

	ret = i2c_smbus_write_byte_data(data->client, RFD77402_CMD_R,
					state | RFD77402_CMD_VALID);
	if (ret < 0)
		return ret;

	usleep_range(10000, 20000);

	ret = i2c_smbus_read_word_data(data->client, RFD77402_STATUS_R);
	if (ret < 0)
		return ret;
	if ((ret & RFD77402_STATUS_PM_MASK) != check)
		return -ENODEV;

	return 0;
}