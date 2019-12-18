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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  bdeSize; scalar_t__ bdeFlags; } ;
struct TYPE_4__ {void* w; TYPE_1__ f; } ;
struct ulp_bde64 {TYPE_2__ tus; void* addrLow; void* addrHigh; } ;
struct nvmefc_ls_req {int /*<<< orphan*/  rqstaddr; int /*<<< orphan*/  rspdma; int /*<<< orphan*/  rqstdma; int /*<<< orphan*/  rsplen; int /*<<< orphan*/  rqstlen; } ;
struct nvme_fc_remote_port {int /*<<< orphan*/  port_id; scalar_t__ private; } ;
struct nvme_fc_local_port {scalar_t__ private; } ;
struct lpfc_vport {int load_flag; int /*<<< orphan*/  phba; } ;
struct lpfc_nvme_rport {struct lpfc_nodelist* ndlp; } ;
struct lpfc_nvme_lport {int /*<<< orphan*/  xmt_ls_err; int /*<<< orphan*/  fc4NvmeLsRequests; struct lpfc_vport* vport; } ;
struct lpfc_nodelist {scalar_t__ nlp_type; scalar_t__ nlp_state; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; scalar_t__ virt; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ BUFF_TYPE_BDE_64I ; 
 int EINVAL ; 
 int ENODEV ; 
 int FC_UNLOADING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_NODE ; 
 int /*<<< orphan*/  LOG_NVME_DISC ; 
 int LOG_NVME_IOERR ; 
 int /*<<< orphan*/  MEM_PRI ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_NVME_INITIATOR ; 
 scalar_t__ NLP_NVME_TARGET ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int WQE_SUCCESS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (void*) ; 
 scalar_t__ lpfc_mbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvme_cmpl_gen_req ; 
 int lpfc_nvme_gen_req (struct lpfc_vport*,struct lpfc_dmabuf*,int /*<<< orphan*/ ,struct nvmefc_ls_req*,int /*<<< orphan*/ ,struct lpfc_nodelist*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int,char*,...) ; 
 void* putPaddrHigh (int /*<<< orphan*/ ) ; 
 void* putPaddrLow (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
lpfc_nvme_ls_req(struct nvme_fc_local_port *pnvme_lport,
		 struct nvme_fc_remote_port *pnvme_rport,
		 struct nvmefc_ls_req *pnvme_lsreq)
{
	int ret = 0;
	struct lpfc_nvme_lport *lport;
	struct lpfc_nvme_rport *rport;
	struct lpfc_vport *vport;
	struct lpfc_nodelist *ndlp;
	struct ulp_bde64 *bpl;
	struct lpfc_dmabuf *bmp;
	uint16_t ntype, nstate;

	/* there are two dma buf in the request, actually there is one and
	 * the second one is just the start address + cmd size.
	 * Before calling lpfc_nvme_gen_req these buffers need to be wrapped
	 * in a lpfc_dmabuf struct. When freeing we just free the wrapper
	 * because the nvem layer owns the data bufs.
	 * We do not have to break these packets open, we don't care what is in
	 * them. And we do not have to look at the resonse data, we only care
	 * that we got a response. All of the caring is going to happen in the
	 * nvme-fc layer.
	 */

	lport = (struct lpfc_nvme_lport *)pnvme_lport->private;
	rport = (struct lpfc_nvme_rport *)pnvme_rport->private;
	if (unlikely(!lport) || unlikely(!rport))
		return -EINVAL;

	vport = lport->vport;

	if (vport->load_flag & FC_UNLOADING)
		return -ENODEV;

	/* Need the ndlp.  It is stored in the driver's rport. */
	ndlp = rport->ndlp;
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp)) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NODE | LOG_NVME_IOERR,
				 "6051 Remoteport x%px, rport has invalid ndlp. "
				 "Failing LS Req\n", pnvme_rport);
		return -ENODEV;
	}

	/* The remote node has to be a mapped nvme target or an
	 * unmapped nvme initiator or it's an error.
	 */
	ntype = ndlp->nlp_type;
	nstate = ndlp->nlp_state;
	if ((ntype & NLP_NVME_TARGET && nstate != NLP_STE_MAPPED_NODE) ||
	    (ntype & NLP_NVME_INITIATOR && nstate != NLP_STE_UNMAPPED_NODE)) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NODE | LOG_NVME_IOERR,
				 "6088 DID x%06x not ready for "
				 "IO. State x%x, Type x%x\n",
				 pnvme_rport->port_id,
				 ndlp->nlp_state, ndlp->nlp_type);
		return -ENODEV;
	}
	bmp = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (!bmp) {

		lpfc_printf_vlog(vport, KERN_ERR, LOG_NVME_DISC,
				 "6044 Could not find node for DID %x\n",
				 pnvme_rport->port_id);
		return 2;
	}
	INIT_LIST_HEAD(&bmp->list);
	bmp->virt = lpfc_mbuf_alloc(vport->phba, MEM_PRI, &(bmp->phys));
	if (!bmp->virt) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NVME_DISC,
				 "6042 Could not find node for DID %x\n",
				 pnvme_rport->port_id);
		kfree(bmp);
		return 3;
	}
	bpl = (struct ulp_bde64 *)bmp->virt;
	bpl->addrHigh = le32_to_cpu(putPaddrHigh(pnvme_lsreq->rqstdma));
	bpl->addrLow = le32_to_cpu(putPaddrLow(pnvme_lsreq->rqstdma));
	bpl->tus.f.bdeFlags = 0;
	bpl->tus.f.bdeSize = pnvme_lsreq->rqstlen;
	bpl->tus.w = le32_to_cpu(bpl->tus.w);
	bpl++;

	bpl->addrHigh = le32_to_cpu(putPaddrHigh(pnvme_lsreq->rspdma));
	bpl->addrLow = le32_to_cpu(putPaddrLow(pnvme_lsreq->rspdma));
	bpl->tus.f.bdeFlags = BUFF_TYPE_BDE_64I;
	bpl->tus.f.bdeSize = pnvme_lsreq->rsplen;
	bpl->tus.w = le32_to_cpu(bpl->tus.w);

	/* Expand print to include key fields. */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_DISC,
			 "6149 Issue LS Req to DID 0x%06x lport x%px, "
			 "rport x%px lsreq x%px rqstlen:%d rsplen:%d "
			 "%pad %pad\n",
			 ndlp->nlp_DID, pnvme_lport, pnvme_rport,
			 pnvme_lsreq, pnvme_lsreq->rqstlen,
			 pnvme_lsreq->rsplen, &pnvme_lsreq->rqstdma,
			 &pnvme_lsreq->rspdma);

	atomic_inc(&lport->fc4NvmeLsRequests);

	/* Hardcode the wait to 30 seconds.  Connections are failing otherwise.
	 * This code allows it all to work.
	 */
	ret = lpfc_nvme_gen_req(vport, bmp, pnvme_lsreq->rqstaddr,
				pnvme_lsreq, lpfc_nvme_cmpl_gen_req,
				ndlp, 2, 30, 0);
	if (ret != WQE_SUCCESS) {
		atomic_inc(&lport->xmt_ls_err);
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NVME_DISC,
				 "6052 EXIT. issue ls wqe failed lport x%px, "
				 "rport x%px lsreq x%px Status %x DID %x\n",
				 pnvme_lport, pnvme_rport, pnvme_lsreq,
				 ret, ndlp->nlp_DID);
		lpfc_mbuf_free(vport->phba, bmp->virt, bmp->phys);
		kfree(bmp);
		return ret;
	}

	/* Stub in routine and return 0 for now. */
	return ret;
}