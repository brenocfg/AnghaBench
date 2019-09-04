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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int MCP_BYTES_PER_MBIT_SHIFT ; 
 int /*<<< orphan*/  MCP_REG_NVM_CFG4 ; 
 int MCP_REG_NVM_CFG4_FLASH_SIZE ; 
 int MCP_REG_NVM_CFG4_FLASH_SIZE_SHIFT ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 

int qed_mcp_get_flash_size(struct qed_hwfn *p_hwfn,
			   struct qed_ptt *p_ptt, u32 *p_flash_size)
{
	u32 flash_size;

	if (IS_VF(p_hwfn->cdev))
		return -EINVAL;

	flash_size = qed_rd(p_hwfn, p_ptt, MCP_REG_NVM_CFG4);
	flash_size = (flash_size & MCP_REG_NVM_CFG4_FLASH_SIZE) >>
		      MCP_REG_NVM_CFG4_FLASH_SIZE_SHIFT;
	flash_size = (1 << (flash_size + MCP_BYTES_PER_MBIT_SHIFT));

	*p_flash_size = flash_size;

	return 0;
}