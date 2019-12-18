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
typedef  int u16 ;
struct dim_channel {scalar_t__ addr; } ;
struct async_tx_dbr {scalar_t__ ch_addr; int rest_size; scalar_t__ rpc; scalar_t__ wpc; scalar_t__* sz_queue; } ;
struct TYPE_2__ {struct async_tx_dbr atx_dbr; } ;

/* Variables and functions */
 int CDT0_RPC_MASK ; 
 int dim2_rpc (scalar_t__) ; 
 TYPE_1__ g ; 
 size_t norm_pc (scalar_t__) ; 

u16 dim_dbr_space(struct dim_channel *ch)
{
	u16 cur_rpc;
	struct async_tx_dbr *dbr = &g.atx_dbr;

	if (ch->addr != dbr->ch_addr)
		return 0xFFFF;

	cur_rpc = dim2_rpc(ch->addr);

	while (norm_pc(dbr->rpc) != cur_rpc) {
		dbr->rest_size += dbr->sz_queue[norm_pc(dbr->rpc)];
		dbr->rpc++;
	}

	if ((u16)(dbr->wpc - dbr->rpc) >= CDT0_RPC_MASK)
		return 0;

	return dbr->rest_size;
}