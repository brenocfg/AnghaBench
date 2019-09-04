#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; } ;
struct TYPE_8__ {scalar_t__ reserved2; scalar_t__ reserved3; scalar_t__ reserved4; TYPE_1__ hdr; } ;
struct TYPE_6__ {unsigned long len; } ;
struct TYPE_7__ {TYPE_2__ hdr; } ;
struct clp_req_rsp_query_pci_grp {TYPE_4__ request; TYPE_3__ response; } ;
struct clp_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLP_LPS_PCI ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int PAGE_SIZE ; 
 scalar_t__ clp_req (struct clp_req_rsp_query_pci_grp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clp_pci_query_grp(struct clp_req *req,
			     struct clp_req_rsp_query_pci_grp *lpcb)
{
	unsigned long limit = PAGE_SIZE - sizeof(lpcb->request);

	if (lpcb->request.hdr.len != sizeof(lpcb->request) ||
	    lpcb->response.hdr.len > limit)
		return -EINVAL;
	if (lpcb->request.reserved2 != 0 || lpcb->request.reserved3 != 0 ||
	    lpcb->request.reserved4 != 0)
		return -EINVAL;
	return clp_req(lpcb, CLP_LPS_PCI) ? -EOPNOTSUPP : 0;
}