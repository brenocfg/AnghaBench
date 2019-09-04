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
struct sdma_txreq {size_t num_desc; int flags; TYPE_1__* descp; } ;
struct hfi1_devdata {int default_desc1; } ;
struct TYPE_2__ {int* qw; } ;

/* Variables and functions */
 int SDMA_DESC0_LAST_DESC_FLAG ; 
 int SDMA_DESC1_HEAD_TO_HOST_FLAG ; 
 int SDMA_DESC1_INT_REQ_FLAG ; 
 int SDMA_TXREQ_F_URGENT ; 

__attribute__((used)) static inline void _sdma_close_tx(struct hfi1_devdata *dd,
				  struct sdma_txreq *tx)
{
	tx->descp[tx->num_desc].qw[0] |=
		SDMA_DESC0_LAST_DESC_FLAG;
	tx->descp[tx->num_desc].qw[1] |=
		dd->default_desc1;
	if (tx->flags & SDMA_TXREQ_F_URGENT)
		tx->descp[tx->num_desc].qw[1] |=
			(SDMA_DESC1_HEAD_TO_HOST_FLAG |
			 SDMA_DESC1_INT_REQ_FLAG);
}