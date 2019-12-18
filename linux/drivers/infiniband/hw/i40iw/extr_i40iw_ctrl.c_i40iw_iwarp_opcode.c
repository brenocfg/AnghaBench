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
typedef  int u32 ;
struct i40iw_aeqe_info {scalar_t__ q2_data_written; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i40iw_iwarp_opcode(struct i40iw_aeqe_info *info, u8 *pkt)
{
	__be16 *mpa;
	u32 opcode = 0xffffffff;

	if (info->q2_data_written) {
		mpa = (__be16 *)pkt;
		opcode = ntohs(mpa[1]) & 0xf;
	}
	return opcode;
}