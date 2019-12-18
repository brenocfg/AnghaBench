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
struct qedi_ctx {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * req_buf; int /*<<< orphan*/  req_dma_addr; int /*<<< orphan*/ * resp_buf; int /*<<< orphan*/  resp_dma_addr; int /*<<< orphan*/ * req_bd_tbl; int /*<<< orphan*/  req_bd_dma; int /*<<< orphan*/ * resp_bd_tbl; int /*<<< orphan*/  resp_bd_dma; } ;
struct qedi_conn {TYPE_2__ gen_pdu; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  QEDI_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedi_conn_free_login_resources(struct qedi_ctx *qedi,
					   struct qedi_conn *qedi_conn)
{
	if (qedi_conn->gen_pdu.resp_bd_tbl) {
		dma_free_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				  qedi_conn->gen_pdu.resp_bd_tbl,
				  qedi_conn->gen_pdu.resp_bd_dma);
		qedi_conn->gen_pdu.resp_bd_tbl = NULL;
	}

	if (qedi_conn->gen_pdu.req_bd_tbl) {
		dma_free_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				  qedi_conn->gen_pdu.req_bd_tbl,
				  qedi_conn->gen_pdu.req_bd_dma);
		qedi_conn->gen_pdu.req_bd_tbl = NULL;
	}

	if (qedi_conn->gen_pdu.resp_buf) {
		dma_free_coherent(&qedi->pdev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  qedi_conn->gen_pdu.resp_buf,
				  qedi_conn->gen_pdu.resp_dma_addr);
		qedi_conn->gen_pdu.resp_buf = NULL;
	}

	if (qedi_conn->gen_pdu.req_buf) {
		dma_free_coherent(&qedi->pdev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  qedi_conn->gen_pdu.req_buf,
				  qedi_conn->gen_pdu.req_dma_addr);
		qedi_conn->gen_pdu.req_buf = NULL;
	}
}