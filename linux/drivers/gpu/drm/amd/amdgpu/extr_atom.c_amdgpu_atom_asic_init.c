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
typedef  int /*<<< orphan*/  uint32_t ;
struct atom_context {scalar_t__ cmd_table; scalar_t__ data_table; } ;

/* Variables and functions */
 int ATOM_CMD_INIT ; 
 scalar_t__ ATOM_DATA_FWI_PTR ; 
 scalar_t__ ATOM_FWI_DEFMCLK_PTR ; 
 scalar_t__ ATOM_FWI_DEFSCLK_PTR ; 
 int CU16 (scalar_t__) ; 
 int /*<<< orphan*/  CU32 (scalar_t__) ; 
 int amdgpu_atom_execute_table (struct atom_context*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int amdgpu_atom_asic_init(struct atom_context *ctx)
{
	int hwi = CU16(ctx->data_table + ATOM_DATA_FWI_PTR);
	uint32_t ps[16];
	int ret;

	memset(ps, 0, 64);

	ps[0] = cpu_to_le32(CU32(hwi + ATOM_FWI_DEFSCLK_PTR));
	ps[1] = cpu_to_le32(CU32(hwi + ATOM_FWI_DEFMCLK_PTR));
	if (!ps[0] || !ps[1])
		return 1;

	if (!CU16(ctx->cmd_table + 4 + 2 * ATOM_CMD_INIT))
		return 1;
	ret = amdgpu_atom_execute_table(ctx, ATOM_CMD_INIT, ps);
	if (ret)
		return ret;

	memset(ps, 0, 64);

	return ret;
}