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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_WAIT_INT ; 
 int /*<<< orphan*/  PRO_WRITE_REG ; 
 int /*<<< orphan*/  Pro_DataCount1 ; 
 int /*<<< orphan*/  Pro_TPCParm ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int ms_set_rw_reg_addr (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ms_write_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int mg_set_tpc_para_sub(struct rtsx_chip *chip, int type,
			       u8 mg_entry_num)
{
	int retval;
	u8 buf[6];

	if (type == 0)
		retval = ms_set_rw_reg_addr(chip, 0, 0, Pro_TPCParm, 1);
	else
		retval = ms_set_rw_reg_addr(chip, 0, 0, Pro_DataCount1, 6);

	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	buf[0] = 0;
	buf[1] = 0;
	if (type == 1) {
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = mg_entry_num;
	}
	retval = ms_write_bytes(chip, PRO_WRITE_REG, (type == 0) ? 1 : 6,
				NO_WAIT_INT, buf, 6);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}