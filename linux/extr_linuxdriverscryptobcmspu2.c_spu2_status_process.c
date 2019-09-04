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
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EBADMSG ; 
 scalar_t__ SPU2_INVALID_ICV ; 
 int SPU_INVALID_ICV ; 
 int /*<<< orphan*/  flow_log (char*,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

int spu2_status_process(u8 *statp)
{
	/* SPU2 status is 2 bytes by default - SPU_RX_STATUS_LEN */
	u16 status = le16_to_cpu(*(__le16 *)statp);

	if (status == 0)
		return 0;

	flow_log("rx status is %#x\n", status);
	if (status == SPU2_INVALID_ICV)
		return SPU_INVALID_ICV;

	return -EBADMSG;
}