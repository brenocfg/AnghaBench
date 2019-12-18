#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath10k_ce_pipe {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int (* ce_revoke_recv_next ) (struct ath10k_ce_pipe*,void**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct ath10k_ce_pipe*,void**,int /*<<< orphan*/ *) ; 

int ath10k_ce_revoke_recv_next(struct ath10k_ce_pipe *ce_state,
			       void **per_transfer_contextp,
			       dma_addr_t *bufferp)
{
	return ce_state->ops->ce_revoke_recv_next(ce_state,
						  per_transfer_contextp,
						  bufferp);
}