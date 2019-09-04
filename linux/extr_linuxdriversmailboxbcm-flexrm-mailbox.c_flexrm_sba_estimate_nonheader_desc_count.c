#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {size_t cmds_count; TYPE_1__* cmds; } ;
struct brcm_message {TYPE_2__ sba; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int BRCM_SBA_CMD_HAS_OUTPUT ; 
 int BRCM_SBA_CMD_HAS_RESP ; 
 int BRCM_SBA_CMD_TYPE_B ; 
 int BRCM_SBA_CMD_TYPE_C ; 

__attribute__((used)) static u32 flexrm_sba_estimate_nonheader_desc_count(struct brcm_message *msg)
{
	u32 i, cnt;

	cnt = 0;
	for (i = 0; i < msg->sba.cmds_count; i++) {
		cnt++;

		if ((msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_B) ||
		    (msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_C))
			cnt++;

		if (msg->sba.cmds[i].flags & BRCM_SBA_CMD_HAS_RESP)
			cnt++;

		if (msg->sba.cmds[i].flags & BRCM_SBA_CMD_HAS_OUTPUT)
			cnt++;
	}

	return cnt;
}