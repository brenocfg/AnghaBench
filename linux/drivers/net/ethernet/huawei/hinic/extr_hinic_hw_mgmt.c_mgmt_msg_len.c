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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MGMT_MSG_LEN_MIN ; 
 int /*<<< orphan*/  MGMT_MSG_LEN_STEP ; 
 scalar_t__ MGMT_MSG_RSVD_FOR_DEV ; 

__attribute__((used)) static u16 mgmt_msg_len(u16 msg_data_len)
{
	/* RSVD + HEADER_SIZE + DATA_LEN */
	u16 msg_len = MGMT_MSG_RSVD_FOR_DEV + sizeof(u64) + msg_data_len;

	if (msg_len > MGMT_MSG_LEN_MIN)
		msg_len = MGMT_MSG_LEN_MIN +
			   ALIGN((msg_len - MGMT_MSG_LEN_MIN),
				 MGMT_MSG_LEN_STEP);
	else
		msg_len = MGMT_MSG_LEN_MIN;

	return msg_len;
}