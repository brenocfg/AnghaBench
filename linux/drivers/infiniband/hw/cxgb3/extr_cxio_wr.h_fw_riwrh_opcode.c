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
struct fw_riwrh {int /*<<< orphan*/  op_seop_flags; } ;
typedef  enum t3_wr_opcode { ____Placeholder_t3_wr_opcode } t3_wr_opcode ;

/* Variables and functions */
 int G_FW_RIWR_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum t3_wr_opcode fw_riwrh_opcode(struct fw_riwrh *wqe)
{
	return G_FW_RIWR_OP(be32_to_cpu(wqe->op_seop_flags));
}