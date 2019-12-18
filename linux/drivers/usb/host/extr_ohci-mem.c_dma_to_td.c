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
struct td {scalar_t__ td_dma; struct td* td_hash; } ;
struct ohci_hcd {struct td** td_hash; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 size_t TD_HASH_FUNC (scalar_t__) ; 
 scalar_t__ TD_MASK ; 

__attribute__((used)) static inline struct td *
dma_to_td (struct ohci_hcd *hc, dma_addr_t td_dma)
{
	struct td *td;

	td_dma &= TD_MASK;
	td = hc->td_hash [TD_HASH_FUNC(td_dma)];
	while (td && td->td_dma != td_dma)
		td = td->td_hash;
	return td;
}