#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_5__ {size_t ncci_ring_list; TYPE_1__* adapter; scalar_t__ nl_req; } ;
struct TYPE_4__ {size_t* ncci_ch; int* ch_flow_control; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 int N_OK_FC_PENDING ; 

__attribute__((used)) static byte plci_nl_busy(PLCI *plci)
{
	/* only applicable for non-multiplexed protocols */
	return (plci->nl_req
		|| (plci->ncci_ring_list
		    && plci->adapter->ncci_ch[plci->ncci_ring_list]
		    && (plci->adapter->ch_flow_control[plci->adapter->ncci_ch[plci->ncci_ring_list]] & N_OK_FC_PENDING)));
}