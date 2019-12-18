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
struct hinic_api_cmd_chain {int chain_type; int /*<<< orphan*/  prod_idx; struct hinic_hwif* hwif; } ;
typedef  enum hinic_api_cmd_chain_type { ____Placeholder_hinic_api_cmd_chain_type } hinic_api_cmd_chain_type ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_API_CMD_PI_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_API_CMD_PI_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_CSR_API_CMD_CHAIN_PI_ADDR (int) ; 
 int /*<<< orphan*/  IDX ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_prod_idx(struct hinic_api_cmd_chain *chain)
{
	enum hinic_api_cmd_chain_type chain_type = chain->chain_type;
	struct hinic_hwif *hwif = chain->hwif;
	u32 addr, prod_idx;

	addr = HINIC_CSR_API_CMD_CHAIN_PI_ADDR(chain_type);
	prod_idx = hinic_hwif_read_reg(hwif, addr);

	prod_idx = HINIC_API_CMD_PI_CLEAR(prod_idx, IDX);

	prod_idx |= HINIC_API_CMD_PI_SET(chain->prod_idx, IDX);

	hinic_hwif_write_reg(hwif, addr, prod_idx);
}