#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_8__ {int /*<<< orphan*/  opaque; scalar_t__* reserved_zero; } ;
struct TYPE_9__ {TYPE_3__ iscsi_opaque; } ;
struct TYPE_7__ {void* lo; void* hi; } ;
struct scsi_bd {TYPE_4__ opaque; TYPE_2__ address; } ;
struct qedi_ctx {int bdq_pbl_mem_size; int rq_num_entries; int bdq_pbl_dma; int bdq_pbl_list_dma; int bdq_pbl_list_num_entries; void* bdq_pbl_list; int /*<<< orphan*/  dbg_ctx; TYPE_5__* pdev; TYPE_1__* bdq; void* bdq_pbl; } ;
typedef  int dma_addr_t ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int buf_dma; void* buf_addr; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QEDI_BDQ_BUF_SIZE ; 
 int QEDI_BDQ_NUM ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDI_LOG_CONN ; 
 int QEDI_PAGE_SIZE ; 
 int /*<<< orphan*/  QEDI_U64_HI (int) ; 
 int /*<<< orphan*/  QEDI_U64_LO (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_alloc_bdq(struct qedi_ctx *qedi)
{
	int i;
	struct scsi_bd *pbl;
	u64 *list;
	dma_addr_t page;

	/* Alloc dma memory for BDQ buffers */
	for (i = 0; i < QEDI_BDQ_NUM; i++) {
		qedi->bdq[i].buf_addr =
				dma_alloc_coherent(&qedi->pdev->dev,
						   QEDI_BDQ_BUF_SIZE,
						   &qedi->bdq[i].buf_dma,
						   GFP_KERNEL);
		if (!qedi->bdq[i].buf_addr) {
			QEDI_ERR(&qedi->dbg_ctx,
				 "Could not allocate BDQ buffer %d.\n", i);
			return -ENOMEM;
		}
	}

	/* Alloc dma memory for BDQ page buffer list */
	qedi->bdq_pbl_mem_size = QEDI_BDQ_NUM * sizeof(struct scsi_bd);
	qedi->bdq_pbl_mem_size = ALIGN(qedi->bdq_pbl_mem_size, QEDI_PAGE_SIZE);
	qedi->rq_num_entries = qedi->bdq_pbl_mem_size / sizeof(struct scsi_bd);

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN, "rq_num_entries = %d.\n",
		  qedi->rq_num_entries);

	qedi->bdq_pbl = dma_alloc_coherent(&qedi->pdev->dev,
					   qedi->bdq_pbl_mem_size,
					   &qedi->bdq_pbl_dma, GFP_KERNEL);
	if (!qedi->bdq_pbl) {
		QEDI_ERR(&qedi->dbg_ctx, "Could not allocate BDQ PBL.\n");
		return -ENOMEM;
	}

	/*
	 * Populate BDQ PBL with physical and virtual address of individual
	 * BDQ buffers
	 */
	pbl = (struct scsi_bd  *)qedi->bdq_pbl;
	for (i = 0; i < QEDI_BDQ_NUM; i++) {
		pbl->address.hi =
				cpu_to_le32(QEDI_U64_HI(qedi->bdq[i].buf_dma));
		pbl->address.lo =
				cpu_to_le32(QEDI_U64_LO(qedi->bdq[i].buf_dma));
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "pbl [0x%p] pbl->address hi [0x%llx] lo [0x%llx], idx [%d]\n",
			  pbl, pbl->address.hi, pbl->address.lo, i);
		pbl->opaque.iscsi_opaque.reserved_zero[0] = 0;
		pbl->opaque.iscsi_opaque.reserved_zero[1] = 0;
		pbl->opaque.iscsi_opaque.reserved_zero[2] = 0;
		pbl->opaque.iscsi_opaque.opaque = cpu_to_le16(i);
		pbl++;
	}

	/* Allocate list of PBL pages */
	qedi->bdq_pbl_list = dma_alloc_coherent(&qedi->pdev->dev,
						QEDI_PAGE_SIZE,
						&qedi->bdq_pbl_list_dma,
						GFP_KERNEL);
	if (!qedi->bdq_pbl_list) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "Could not allocate list of PBL pages.\n");
		return -ENOMEM;
	}

	/*
	 * Now populate PBL list with pages that contain pointers to the
	 * individual buffers.
	 */
	qedi->bdq_pbl_list_num_entries = qedi->bdq_pbl_mem_size /
					 QEDI_PAGE_SIZE;
	list = (u64 *)qedi->bdq_pbl_list;
	page = qedi->bdq_pbl_list_dma;
	for (i = 0; i < qedi->bdq_pbl_list_num_entries; i++) {
		*list = qedi->bdq_pbl_dma;
		list++;
		page += QEDI_PAGE_SIZE;
	}

	return 0;
}