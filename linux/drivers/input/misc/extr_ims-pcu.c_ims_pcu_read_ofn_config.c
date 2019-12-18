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
struct ims_pcu {int /*<<< orphan*/ * cmd_buf; } ;
typedef  scalar_t__ s16 ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OFN_GET_CONFIG ; 
 int OFN_REG_RESULT_OFFSET ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int ims_pcu_execute_command (struct ims_pcu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ims_pcu_read_ofn_config(struct ims_pcu *pcu, u8 addr, u8 *data)
{
	int error;
	s16 result;

	error = ims_pcu_execute_command(pcu, OFN_GET_CONFIG,
					&addr, sizeof(addr));
	if (error)
		return error;

	result = (s16)get_unaligned_le16(pcu->cmd_buf + OFN_REG_RESULT_OFFSET);
	if (result < 0)
		return -EIO;

	/* We only need LSB */
	*data = pcu->cmd_buf[OFN_REG_RESULT_OFFSET];
	return 0;
}