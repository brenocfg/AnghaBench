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
struct clp_req_hdr {int cmd; } ;
struct clp_req {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int clp_pci_list (struct clp_req*,void*) ; 
 int clp_pci_query (struct clp_req*,void*) ; 
 int clp_pci_query_grp (struct clp_req*,void*) ; 
 int clp_pci_slpc (struct clp_req*,void*) ; 

__attribute__((used)) static int clp_pci_command(struct clp_req *req, struct clp_req_hdr *lpcb)
{
	switch (lpcb->cmd) {
	case 0x0001: /* store logical-processor characteristics */
		return clp_pci_slpc(req, (void *) lpcb);
	case 0x0002: /* list PCI functions */
		return clp_pci_list(req, (void *) lpcb);
	case 0x0003: /* query PCI function */
		return clp_pci_query(req, (void *) lpcb);
	case 0x0004: /* query PCI function group */
		return clp_pci_query_grp(req, (void *) lpcb);
	default:
		return -EINVAL;
	}
}