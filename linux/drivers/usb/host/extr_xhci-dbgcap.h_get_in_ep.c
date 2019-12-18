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
struct xhci_hcd {struct xhci_dbc* dbc; } ;
struct xhci_dbc {struct dbc_ep* eps; } ;
struct dbc_ep {int dummy; } ;

/* Variables and functions */
 size_t BULK_IN ; 

__attribute__((used)) static inline struct dbc_ep *get_in_ep(struct xhci_hcd *xhci)
{
	struct xhci_dbc		*dbc = xhci->dbc;

	return &dbc->eps[BULK_IN];
}