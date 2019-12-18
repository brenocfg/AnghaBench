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
struct ocrdma_cqe {int /*<<< orphan*/  flags_status_srcqpn; } ;

/* Variables and functions */
 int OCRDMA_CQE_WRITE_IMM ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_cqe_wr_imm(struct ocrdma_cqe *cqe)
{
	return (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_WRITE_IMM) ? 1 : 0;
}