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
typedef  int u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct scatterlist {int dummy; } ;
struct TYPE_3__ {struct scatterlist smp_req; struct scatterlist smp_resp; } ;
struct sas_task {TYPE_1__ smp_task; int /*<<< orphan*/  scatter; struct domain_device* dev; } ;
struct sas_phy {size_t number; } ;
struct sas_ha_struct {struct asd_sas_phy** sas_phy; } ;
struct mvs_task_exec_info {size_t tag; size_t n_elem; struct sas_task* task; struct mvs_cmd_hdr* hdr; } ;
struct mvs_slot_info {int buf_dma; size_t tx; void* response; void* buf; } ;
struct mvs_info {int flags; size_t tx_prod; int /*<<< orphan*/  dev; void** tx; struct mvs_slot_info* slot_info; struct sas_ha_struct* sas; } ;
struct mvs_cmd_hdr {size_t flags; scalar_t__ data_len; void* tags; void* lens; scalar_t__* reserved; void* status_buf; void* prd_tbl; void* open_frame; void* cmd_tbl; } ;
struct domain_device {int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  linkrate; struct sas_phy* phy; struct asd_sas_port* port; } ;
struct asd_sas_port {int /*<<< orphan*/  linkrate; } ;
struct asd_sas_phy {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int (* prd_size ) () ;int /*<<< orphan*/  (* make_prd ) (int /*<<< orphan*/ ,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t MCH_PRD_LEN_SHIFT ; 
 int MVF_FLAG_SOC ; 
 TYPE_2__* MVS_CHIP_DISP ; 
 scalar_t__ MVS_OAF_SZ ; 
 size_t MVS_PHY_ID ; 
 int PROTOCOL_SMP ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 size_t SB_RFB_MAX ; 
 size_t TXQ_CMD_SHIFT ; 
 size_t TXQ_CMD_SMP ; 
 size_t TXQ_MODE_I ; 
 size_t TXQ_PHY_SHIFT ; 
 void* cpu_to_le32 (size_t) ; 
 void* cpu_to_le64 (int) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sg_dma_address (struct scatterlist*) ; 
 size_t sg_dma_len (struct scatterlist*) ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static int mvs_task_prep_smp(struct mvs_info *mvi,
			     struct mvs_task_exec_info *tei)
{
	int elem, rc, i;
	struct sas_ha_struct *sha = mvi->sas;
	struct sas_task *task = tei->task;
	struct mvs_cmd_hdr *hdr = tei->hdr;
	struct domain_device *dev = task->dev;
	struct asd_sas_port *sas_port = dev->port;
	struct sas_phy *sphy = dev->phy;
	struct asd_sas_phy *sas_phy = sha->sas_phy[sphy->number];
	struct scatterlist *sg_req, *sg_resp;
	u32 req_len, resp_len, tag = tei->tag;
	void *buf_tmp;
	u8 *buf_oaf;
	dma_addr_t buf_tmp_dma;
	void *buf_prd;
	struct mvs_slot_info *slot = &mvi->slot_info[tag];
	u32 flags = (tei->n_elem << MCH_PRD_LEN_SHIFT);

	/*
	 * DMA-map SMP request, response buffers
	 */
	sg_req = &task->smp_task.smp_req;
	elem = dma_map_sg(mvi->dev, sg_req, 1, DMA_TO_DEVICE);
	if (!elem)
		return -ENOMEM;
	req_len = sg_dma_len(sg_req);

	sg_resp = &task->smp_task.smp_resp;
	elem = dma_map_sg(mvi->dev, sg_resp, 1, DMA_FROM_DEVICE);
	if (!elem) {
		rc = -ENOMEM;
		goto err_out;
	}
	resp_len = SB_RFB_MAX;

	/* must be in dwords */
	if ((req_len & 0x3) || (resp_len & 0x3)) {
		rc = -EINVAL;
		goto err_out_2;
	}

	/*
	 * arrange MVS_SLOT_BUF_SZ-sized DMA buffer according to our needs
	 */

	/* region 1: command table area (MVS_SSP_CMD_SZ bytes) ***** */
	buf_tmp = slot->buf;
	buf_tmp_dma = slot->buf_dma;

	hdr->cmd_tbl = cpu_to_le64(sg_dma_address(sg_req));

	/* region 2: open address frame area (MVS_OAF_SZ bytes) ********* */
	buf_oaf = buf_tmp;
	hdr->open_frame = cpu_to_le64(buf_tmp_dma);

	buf_tmp += MVS_OAF_SZ;
	buf_tmp_dma += MVS_OAF_SZ;

	/* region 3: PRD table *********************************** */
	buf_prd = buf_tmp;
	if (tei->n_elem)
		hdr->prd_tbl = cpu_to_le64(buf_tmp_dma);
	else
		hdr->prd_tbl = 0;

	i = MVS_CHIP_DISP->prd_size() * tei->n_elem;
	buf_tmp += i;
	buf_tmp_dma += i;

	/* region 4: status buffer (larger the PRD, smaller this buf) ****** */
	slot->response = buf_tmp;
	hdr->status_buf = cpu_to_le64(buf_tmp_dma);
	if (mvi->flags & MVF_FLAG_SOC)
		hdr->reserved[0] = 0;

	/*
	 * Fill in TX ring and command slot header
	 */
	slot->tx = mvi->tx_prod;
	mvi->tx[mvi->tx_prod] = cpu_to_le32((TXQ_CMD_SMP << TXQ_CMD_SHIFT) |
					TXQ_MODE_I | tag |
					(MVS_PHY_ID << TXQ_PHY_SHIFT));

	hdr->flags |= flags;
	hdr->lens = cpu_to_le32(((resp_len / 4) << 16) | ((req_len - 4) / 4));
	hdr->tags = cpu_to_le32(tag);
	hdr->data_len = 0;

	/* generate open address frame hdr (first 12 bytes) */
	/* initiator, SMP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PROTOCOL_SMP << 4) | 0x01;
	buf_oaf[1] = min(sas_port->linkrate, dev->linkrate) & 0xf;
	*(u16 *)(buf_oaf + 2) = 0xFFFF;		/* SAS SPEC */
	memcpy(buf_oaf + 4, dev->sas_addr, SAS_ADDR_SIZE);

	/* fill in PRD (scatter/gather) table, if any */
	MVS_CHIP_DISP->make_prd(task->scatter, tei->n_elem, buf_prd);

	return 0;

err_out_2:
	dma_unmap_sg(mvi->dev, &tei->task->smp_task.smp_resp, 1,
		     DMA_FROM_DEVICE);
err_out:
	dma_unmap_sg(mvi->dev, &tei->task->smp_task.smp_req, 1,
		     DMA_TO_DEVICE);
	return rc;
}