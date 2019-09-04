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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_hwif {int dummy; } ;
struct hinic_api_cmd_chain {int /*<<< orphan*/  num_cells; int /*<<< orphan*/  chain_type; struct hinic_hwif* hwif; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_CSR_API_CMD_CHAIN_NUM_CELLS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void api_cmd_set_num_cells(struct hinic_api_cmd_chain *chain)
{
	struct hinic_hwif *hwif = chain->hwif;
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_CHAIN_NUM_CELLS_ADDR(chain->chain_type);
	val  = chain->num_cells;
	hinic_hwif_write_reg(hwif, addr, val);
}