#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* cmd_req_virt; int /*<<< orphan*/  group_prom; int /*<<< orphan*/  ind_group_prom; } ;
struct TYPE_8__ {TYPE_1__* item; } ;
struct TYPE_9__ {TYPE_2__ filter_set; int /*<<< orphan*/  cmd_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  item_code; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ DFX_board_t ;

/* Variables and functions */
 int DFX_K_FAILURE ; 
 scalar_t__ DFX_K_SUCCESS ; 
 int /*<<< orphan*/  PI_CMD_K_FILTERS_SET ; 
 int /*<<< orphan*/  PI_FSTATE_K_PASS ; 
 int /*<<< orphan*/  PI_ITEM_K_BROADCAST ; 
 int /*<<< orphan*/  PI_ITEM_K_EOL ; 
 int /*<<< orphan*/  PI_ITEM_K_GROUP_PROM ; 
 int /*<<< orphan*/  PI_ITEM_K_IND_GROUP_PROM ; 
 scalar_t__ dfx_hw_dma_cmd_req (TYPE_4__*) ; 

__attribute__((used)) static int dfx_ctl_update_filters(DFX_board_t *bp)
	{
	int	i = 0;					/* used as index */

	/* Fill in command request information */

	bp->cmd_req_virt->cmd_type = PI_CMD_K_FILTERS_SET;

	/* Initialize Broadcast filter - * ALWAYS ENABLED * */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_BROADCAST;
	bp->cmd_req_virt->filter_set.item[i++].value	= PI_FSTATE_K_PASS;

	/* Initialize LLC Individual/Group Promiscuous filter */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_IND_GROUP_PROM;
	bp->cmd_req_virt->filter_set.item[i++].value	= bp->ind_group_prom;

	/* Initialize LLC Group Promiscuous filter */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_GROUP_PROM;
	bp->cmd_req_virt->filter_set.item[i++].value	= bp->group_prom;

	/* Terminate the item code list */

	bp->cmd_req_virt->filter_set.item[i].item_code	= PI_ITEM_K_EOL;

	/* Issue command to update adapter filters, then return */

	if (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		return DFX_K_FAILURE;
	return DFX_K_SUCCESS;
	}