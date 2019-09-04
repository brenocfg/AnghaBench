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
struct hinic_api_cmd_chain {int /*<<< orphan*/  wb_status_paddr; int /*<<< orphan*/  chain_type; struct hinic_hwif* hwif; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_CSR_API_CMD_STATUS_HI_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_CSR_API_CMD_STATUS_LO_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void api_cmd_set_status_addr(struct hinic_api_cmd_chain *chain)
{
	struct hinic_hwif *hwif = chain->hwif;
	u32 addr, val;

	addr = HINIC_CSR_API_CMD_STATUS_HI_ADDR(chain->chain_type);
	val = upper_32_bits(chain->wb_status_paddr);
	hinic_hwif_write_reg(hwif, addr, val);

	addr = HINIC_CSR_API_CMD_STATUS_LO_ADDR(chain->chain_type);
	val = lower_32_bits(chain->wb_status_paddr);
	hinic_hwif_write_reg(hwif, addr, val);
}