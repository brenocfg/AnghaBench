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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct cmdq_pkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_CODE_WFE ; 
 scalar_t__ CMDQ_MAX_EVENT ; 
 int CMDQ_WFE_UPDATE ; 
 int CMDQ_WFE_WAIT ; 
 int CMDQ_WFE_WAIT_VALUE ; 
 int EINVAL ; 
 int cmdq_pkt_append_command (struct cmdq_pkt*,int /*<<< orphan*/ ,scalar_t__,int) ; 

int cmdq_pkt_wfe(struct cmdq_pkt *pkt, u16 event)
{
	u32 arg_b;

	if (event >= CMDQ_MAX_EVENT)
		return -EINVAL;

	/*
	 * WFE arg_b
	 * bit 0-11: wait value
	 * bit 15: 1 - wait, 0 - no wait
	 * bit 16-27: update value
	 * bit 31: 1 - update, 0 - no update
	 */
	arg_b = CMDQ_WFE_UPDATE | CMDQ_WFE_WAIT | CMDQ_WFE_WAIT_VALUE;

	return cmdq_pkt_append_command(pkt, CMDQ_CODE_WFE, event, arg_b);
}