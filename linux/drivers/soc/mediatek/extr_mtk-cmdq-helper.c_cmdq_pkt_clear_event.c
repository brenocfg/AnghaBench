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
typedef  scalar_t__ u16 ;
struct cmdq_pkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_CODE_WFE ; 
 scalar_t__ CMDQ_MAX_EVENT ; 
 int /*<<< orphan*/  CMDQ_WFE_UPDATE ; 
 int EINVAL ; 
 int cmdq_pkt_append_command (struct cmdq_pkt*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int cmdq_pkt_clear_event(struct cmdq_pkt *pkt, u16 event)
{
	if (event >= CMDQ_MAX_EVENT)
		return -EINVAL;

	return cmdq_pkt_append_command(pkt, CMDQ_CODE_WFE, event,
				       CMDQ_WFE_UPDATE);
}