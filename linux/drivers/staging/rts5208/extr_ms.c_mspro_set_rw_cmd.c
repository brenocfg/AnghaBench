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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int MS_MAX_RETRY_COUNT ; 
 int /*<<< orphan*/  PRO_EX_SET_CMD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WAIT_INT ; 
 int ms_write_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int mspro_set_rw_cmd(struct rtsx_chip *chip,
			    u32 start_sec, u16 sec_cnt, u8 cmd)
{
	int retval, i;
	u8 data[8];

	data[0] = cmd;
	data[1] = (u8)(sec_cnt >> 8);
	data[2] = (u8)sec_cnt;
	data[3] = (u8)(start_sec >> 24);
	data[4] = (u8)(start_sec >> 16);
	data[5] = (u8)(start_sec >> 8);
	data[6] = (u8)start_sec;
	data[7] = 0;

	for (i = 0; i < MS_MAX_RETRY_COUNT; i++) {
		retval = ms_write_bytes(chip, PRO_EX_SET_CMD, 7,
					WAIT_INT, data, 8);
		if (retval == STATUS_SUCCESS)
			break;
	}
	if (i == MS_MAX_RETRY_COUNT)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}