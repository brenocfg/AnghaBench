#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qedi_ctx {TYPE_1__* pdev; int /*<<< orphan*/  dbg_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/ * req_buf; int /*<<< orphan*/  req_dma_addr; int /*<<< orphan*/ * resp_buf; int /*<<< orphan*/  resp_dma_addr; int /*<<< orphan*/ * req_bd_tbl; int /*<<< orphan*/  req_bd_dma; void* resp_bd_tbl; int /*<<< orphan*/  resp_bd_dma; int /*<<< orphan*/ * resp_wr_ptr; int /*<<< orphan*/  resp_buf_size; int /*<<< orphan*/ * req_wr_ptr; scalar_t__ req_buf_size; } ;
struct qedi_conn {TYPE_3__* cls_conn; TYPE_2__ gen_pdu; int /*<<< orphan*/  iscsi_conn_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  dd_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_SESS ; 
 int /*<<< orphan*/  QEDI_PAGE_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int qedi_conn_alloc_login_resources(struct qedi_ctx *qedi,
					   struct qedi_conn *qedi_conn)
{
	qedi_conn->gen_pdu.req_buf =
		dma_alloc_coherent(&qedi->pdev->dev,
				   ISCSI_DEF_MAX_RECV_SEG_LEN,
				   &qedi_conn->gen_pdu.req_dma_addr,
				   GFP_KERNEL);
	if (!qedi_conn->gen_pdu.req_buf)
		goto login_req_buf_failure;

	qedi_conn->gen_pdu.req_buf_size = 0;
	qedi_conn->gen_pdu.req_wr_ptr = qedi_conn->gen_pdu.req_buf;

	qedi_conn->gen_pdu.resp_buf =
		dma_alloc_coherent(&qedi->pdev->dev,
				   ISCSI_DEF_MAX_RECV_SEG_LEN,
				   &qedi_conn->gen_pdu.resp_dma_addr,
				   GFP_KERNEL);
	if (!qedi_conn->gen_pdu.resp_buf)
		goto login_resp_buf_failure;

	qedi_conn->gen_pdu.resp_buf_size = ISCSI_DEF_MAX_RECV_SEG_LEN;
	qedi_conn->gen_pdu.resp_wr_ptr = qedi_conn->gen_pdu.resp_buf;

	qedi_conn->gen_pdu.req_bd_tbl =
		dma_alloc_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				   &qedi_conn->gen_pdu.req_bd_dma, GFP_KERNEL);
	if (!qedi_conn->gen_pdu.req_bd_tbl)
		goto login_req_bd_tbl_failure;

	qedi_conn->gen_pdu.resp_bd_tbl =
		dma_alloc_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				   &qedi_conn->gen_pdu.resp_bd_dma,
				   GFP_KERNEL);
	if (!qedi_conn->gen_pdu.resp_bd_tbl)
		goto login_resp_bd_tbl_failure;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_SESS,
		  "Allocation successful, cid=0x%x\n",
		  qedi_conn->iscsi_conn_id);
	return 0;

login_resp_bd_tbl_failure:
	dma_free_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
			  qedi_conn->gen_pdu.req_bd_tbl,
			  qedi_conn->gen_pdu.req_bd_dma);
	qedi_conn->gen_pdu.req_bd_tbl = NULL;

login_req_bd_tbl_failure:
	dma_free_coherent(&qedi->pdev->dev, ISCSI_DEF_MAX_RECV_SEG_LEN,
			  qedi_conn->gen_pdu.resp_buf,
			  qedi_conn->gen_pdu.resp_dma_addr);
	qedi_conn->gen_pdu.resp_buf = NULL;
login_resp_buf_failure:
	dma_free_coherent(&qedi->pdev->dev, ISCSI_DEF_MAX_RECV_SEG_LEN,
			  qedi_conn->gen_pdu.req_buf,
			  qedi_conn->gen_pdu.req_dma_addr);
	qedi_conn->gen_pdu.req_buf = NULL;
login_req_buf_failure:
	iscsi_conn_printk(KERN_ERR, qedi_conn->cls_conn->dd_data,
			  "login resource alloc failed!!\n");
	return -ENOMEM;
}