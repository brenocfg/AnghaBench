#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbp2_logical_unit {scalar_t__ command_block_agent_address; int /*<<< orphan*/  generation; TYPE_1__* tgt; } ;
struct fw_transaction {int dummy; } ;
struct fw_device {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ SBP2_AGENT_RESET ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  complete_agent_reset_write_no_wait ; 
 int /*<<< orphan*/  fw_send_request (int /*<<< orphan*/ ,struct fw_transaction*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct fw_transaction*) ; 
 struct fw_transaction* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct fw_device* target_parent_device (TYPE_1__*) ; 

__attribute__((used)) static void sbp2_agent_reset_no_wait(struct sbp2_logical_unit *lu)
{
	struct fw_device *device = target_parent_device(lu->tgt);
	struct fw_transaction *t;
	static __be32 d;

	t = kmalloc(sizeof(*t), GFP_ATOMIC);
	if (t == NULL)
		return;

	fw_send_request(device->card, t, TCODE_WRITE_QUADLET_REQUEST,
			lu->tgt->node_id, lu->generation, device->max_speed,
			lu->command_block_agent_address + SBP2_AGENT_RESET,
			&d, 4, complete_agent_reset_write_no_wait, t);
}