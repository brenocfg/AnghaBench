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
struct TYPE_7__ {unsigned long len; } ;
struct TYPE_8__ {TYPE_3__ hdr; } ;
struct TYPE_5__ {int len; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
struct clp_req_rsp_slpc {TYPE_4__ response; TYPE_2__ request; } ;
struct clp_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLP_LPS_PCI ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int PAGE_SIZE ; 
 scalar_t__ clp_req (struct clp_req_rsp_slpc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clp_pci_slpc(struct clp_req *req, struct clp_req_rsp_slpc *lpcb)
{
	unsigned long limit = PAGE_SIZE - sizeof(lpcb->request);

	if (lpcb->request.hdr.len != sizeof(lpcb->request) ||
	    lpcb->response.hdr.len > limit)
		return -EINVAL;
	return clp_req(lpcb, CLP_LPS_PCI) ? -EOPNOTSUPP : 0;
}