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
struct hinic_api_cmd_chain {int /*<<< orphan*/  hwif; int /*<<< orphan*/  chain_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_IDX ; 
 int /*<<< orphan*/  HINIC_API_CMD_STATUS_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_CSR_API_CMD_STATUS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_hw_cons_idx(struct hinic_api_cmd_chain *chain)
{
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_STATUS_ADDR(chain->chain_type);
	val  = hinic_hwif_read_reg(chain->hwif, addr);

	return HINIC_API_CMD_STATUS_GET(val, CONS_IDX);
}