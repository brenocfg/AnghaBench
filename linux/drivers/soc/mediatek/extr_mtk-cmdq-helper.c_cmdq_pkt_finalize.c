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
struct cmdq_pkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_CODE_EOC ; 
 int /*<<< orphan*/  CMDQ_CODE_JUMP ; 
 int /*<<< orphan*/  CMDQ_EOC_IRQ_EN ; 
 int /*<<< orphan*/  CMDQ_JUMP_PASS ; 
 int cmdq_pkt_append_command (struct cmdq_pkt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmdq_pkt_finalize(struct cmdq_pkt *pkt)
{
	int err;

	/* insert EOC and generate IRQ for each command iteration */
	err = cmdq_pkt_append_command(pkt, CMDQ_CODE_EOC, 0, CMDQ_EOC_IRQ_EN);

	/* JUMP to end */
	err |= cmdq_pkt_append_command(pkt, CMDQ_CODE_JUMP, 0, CMDQ_JUMP_PASS);

	return err;
}