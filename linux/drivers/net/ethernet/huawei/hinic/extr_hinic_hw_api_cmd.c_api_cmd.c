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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_api_cmd_chain {size_t prod_idx; int /*<<< orphan*/  sem; int /*<<< orphan*/  curr_node; struct hinic_api_cmd_cell_ctxt* cell_ctxt; } ;
struct hinic_api_cmd_cell_ctxt {int /*<<< orphan*/  cell_vaddr; } ;
typedef  enum hinic_node_id { ____Placeholder_hinic_node_id } hinic_node_id ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ chain_busy (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  cmd_chain_prod_idx_inc (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_cell (struct hinic_api_cmd_chain*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_prod_idx (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int wait_for_api_cmd_completion (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int api_cmd(struct hinic_api_cmd_chain *chain,
		   enum hinic_node_id dest, u8 *cmd, u16 cmd_size)
{
	struct hinic_api_cmd_cell_ctxt *ctxt;
	int err;

	down(&chain->sem);
	if (chain_busy(chain)) {
		up(&chain->sem);
		return -EBUSY;
	}

	prepare_cell(chain, dest, cmd, cmd_size);
	cmd_chain_prod_idx_inc(chain);

	wmb();  /* inc pi before issue the command */

	set_prod_idx(chain);    /* issue the command */

	ctxt = &chain->cell_ctxt[chain->prod_idx];

	chain->curr_node = ctxt->cell_vaddr;

	err = wait_for_api_cmd_completion(chain);

	up(&chain->sem);
	return err;
}