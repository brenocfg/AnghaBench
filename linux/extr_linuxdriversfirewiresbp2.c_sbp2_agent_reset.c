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
struct fw_device {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 scalar_t__ SBP2_AGENT_RESET ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  fw_run_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 struct fw_device* target_parent_device (TYPE_1__*) ; 

__attribute__((used)) static void sbp2_agent_reset(struct sbp2_logical_unit *lu)
{
	struct fw_device *device = target_parent_device(lu->tgt);
	__be32 d = 0;

	fw_run_transaction(device->card, TCODE_WRITE_QUADLET_REQUEST,
			   lu->tgt->node_id, lu->generation, device->max_speed,
			   lu->command_block_agent_address + SBP2_AGENT_RESET,
			   &d, 4);
}