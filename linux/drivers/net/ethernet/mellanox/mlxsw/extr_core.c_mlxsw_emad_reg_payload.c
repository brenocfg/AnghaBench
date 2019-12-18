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

/* Variables and functions */
 int MLXSW_EMAD_OP_TLV_LEN ; 

__attribute__((used)) static char *mlxsw_emad_reg_payload(const char *op_tlv)
{
	return ((char *) (op_tlv + (MLXSW_EMAD_OP_TLV_LEN + 1) * sizeof(u32)));
}