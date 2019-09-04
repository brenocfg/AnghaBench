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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {scalar_t__ rsp; int len; } ;
struct TYPE_8__ {TYPE_3__ hdr; int /*<<< orphan*/  fh; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {void* ndas; void* oc; int /*<<< orphan*/  fh; TYPE_1__ hdr; } ;
struct clp_req_rsp_set_pci {TYPE_4__ response; TYPE_2__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLP_LPS_PCI ; 
 scalar_t__ CLP_RC_OK ; 
 scalar_t__ CLP_RC_SETPCIFN_BUSY ; 
 int /*<<< orphan*/  CLP_SET_PCI_FN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct clp_req_rsp_set_pci* clp_alloc_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clp_free_block (struct clp_req_rsp_set_pci*) ; 
 int clp_req (struct clp_req_rsp_set_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct clp_req_rsp_set_pci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  zpci_err (char*) ; 
 int /*<<< orphan*/  zpci_err_clp (scalar_t__,int) ; 

__attribute__((used)) static int clp_set_pci_fn(u32 *fh, u8 nr_dma_as, u8 command)
{
	struct clp_req_rsp_set_pci *rrb;
	int rc, retries = 100;

	rrb = clp_alloc_block(GFP_KERNEL);
	if (!rrb)
		return -ENOMEM;

	do {
		memset(rrb, 0, sizeof(*rrb));
		rrb->request.hdr.len = sizeof(rrb->request);
		rrb->request.hdr.cmd = CLP_SET_PCI_FN;
		rrb->response.hdr.len = sizeof(rrb->response);
		rrb->request.fh = *fh;
		rrb->request.oc = command;
		rrb->request.ndas = nr_dma_as;

		rc = clp_req(rrb, CLP_LPS_PCI);
		if (rrb->response.hdr.rsp == CLP_RC_SETPCIFN_BUSY) {
			retries--;
			if (retries < 0)
				break;
			msleep(20);
		}
	} while (rrb->response.hdr.rsp == CLP_RC_SETPCIFN_BUSY);

	if (!rc && rrb->response.hdr.rsp == CLP_RC_OK)
		*fh = rrb->response.fh;
	else {
		zpci_err("Set PCI FN:\n");
		zpci_err_clp(rrb->response.hdr.rsp, rc);
		rc = -EIO;
	}
	clp_free_block(rrb);
	return rc;
}