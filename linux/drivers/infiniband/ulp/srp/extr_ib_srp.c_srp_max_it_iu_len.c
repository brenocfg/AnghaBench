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
typedef  scalar_t__ uint32_t ;
struct srp_indirect_buf {int dummy; } ;
struct srp_direct_buf {int dummy; } ;
struct srp_cmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRP_IMM_DATA_OFFSET ; 
 scalar_t__ SRP_MAX_ADD_CDB_LEN ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ srp_max_imm_data ; 

__attribute__((used)) static uint32_t srp_max_it_iu_len(int cmd_sg_cnt, bool use_imm_data)
{
	uint32_t max_iu_len = sizeof(struct srp_cmd) + SRP_MAX_ADD_CDB_LEN +
		sizeof(struct srp_indirect_buf) +
		cmd_sg_cnt * sizeof(struct srp_direct_buf);

	if (use_imm_data)
		max_iu_len = max(max_iu_len, SRP_IMM_DATA_OFFSET +
				 srp_max_imm_data);

	return max_iu_len;
}