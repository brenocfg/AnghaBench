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
struct cyapa {int dummy; } ;
typedef  int /*<<< orphan*/  resp_data ;
typedef  int /*<<< orphan*/  bl_gen5_bl_exit ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int PIP_BL_FAIL_EXIT_RESP_LEN ; 
 int PIP_BL_RESP_REPORT_ID ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_sort_pip_bl_exit_data ; 

int cyapa_pip_bl_exit(struct cyapa *cyapa)
{

	u8 bl_gen5_bl_exit[] = { 0x04, 0x00,
		0x0B, 0x00, 0x40, 0x00, 0x01, 0x3b, 0x00, 0x00,
		0x20, 0xc7, 0x17
	};
	u8 resp_data[11];
	int resp_len;
	int error;

	resp_len = sizeof(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			bl_gen5_bl_exit, sizeof(bl_gen5_bl_exit),
			resp_data, &resp_len,
			5000, cyapa_sort_pip_bl_exit_data, false);
	if (error)
		return error;

	if (resp_len == PIP_BL_FAIL_EXIT_RESP_LEN ||
			resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID)
		return -EAGAIN;

	if (resp_data[0] == 0x00 && resp_data[1] == 0x00)
		return 0;

	return -ENODEV;
}