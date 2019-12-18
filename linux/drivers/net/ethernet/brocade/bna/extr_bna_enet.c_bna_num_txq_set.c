#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_txq; scalar_t__ fw_query_complete; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct bna {TYPE_2__ ioceth; } ;

/* Variables and functions */
 int BNA_CB_FAIL ; 
 int BNA_CB_SUCCESS ; 

int
bna_num_txq_set(struct bna *bna, int num_txq)
{
	if (bna->ioceth.attr.fw_query_complete &&
		(num_txq <= bna->ioceth.attr.num_txq)) {
		bna->ioceth.attr.num_txq = num_txq;
		return BNA_CB_SUCCESS;
	}

	return BNA_CB_FAIL;
}