#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_10__ {scalar_t__ exchoffld_enabled; } ;
struct qla_hw_data {int exchoffld_size; int max_exchg; scalar_t__ init_cb; TYPE_1__ flags; int /*<<< orphan*/  exchoffld_buf; TYPE_8__* pdev; int /*<<< orphan*/  exchoffld_buf_dma; } ;
struct init_cb_81xx {scalar_t__ exchange_count; } ;
struct TYPE_11__ {int /*<<< orphan*/  ql2xexchoffld; struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FW_DEF_EXCHANGES_CNT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_EXCHG_OFFLD_CAPABLE (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
 int REDUCE_EXCHANGES_CNT ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_pci (int /*<<< orphan*/ ,TYPE_8__*,int,char*) ; 
 int /*<<< orphan*/  qla2x00_free_exchoffld_buffer (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2x00_number_of_exch (TYPE_2__*,int*,int) ; 
 int qla_get_exchoffld_status (TYPE_2__*,int*,int*) ; 
 scalar_t__ qla_ini_mode_enabled (TYPE_2__*) ; 
 int qla_set_exchoffld_mem_cfg (TYPE_2__*) ; 

int
qla2x00_set_exchoffld_buffer(scsi_qla_host_t *vha)
{
	int rval;
	u16	size, max_cnt;
	u32 actual_cnt, totsz;
	struct qla_hw_data *ha = vha->hw;

	if (!ha->flags.exchoffld_enabled)
		return QLA_SUCCESS;

	if (!IS_EXCHG_OFFLD_CAPABLE(ha))
		return QLA_SUCCESS;

	max_cnt = 0;
	rval = qla_get_exchoffld_status(vha, &size, &max_cnt);
	if (rval != QLA_SUCCESS) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0xd012,
		    "Failed to get exlogin status.\n");
		return rval;
	}

	qla2x00_number_of_exch(vha, &actual_cnt, max_cnt);
	ql_log(ql_log_info, vha, 0xd014,
	    "Actual exchange offload count: %d.\n", actual_cnt);

	totsz = actual_cnt * size;

	if (totsz != ha->exchoffld_size) {
		qla2x00_free_exchoffld_buffer(ha);
		if (actual_cnt <= FW_DEF_EXCHANGES_CNT) {
			ha->exchoffld_size = 0;
			ha->flags.exchoffld_enabled = 0;
			return QLA_SUCCESS;
		}

		ha->exchoffld_size = totsz;

		ql_log(ql_log_info, vha, 0xd016,
		    "Exchange offload: max_count=%d, actual count=%d entry sz=0x%x, total sz=0x%x\n",
		    max_cnt, actual_cnt, size, totsz);

		ql_log(ql_log_info, vha, 0xd017,
		    "Exchange Buffers requested size = 0x%x\n",
		    ha->exchoffld_size);

		/* Get consistent memory for extended logins */
		ha->exchoffld_buf = dma_alloc_coherent(&ha->pdev->dev,
			ha->exchoffld_size, &ha->exchoffld_buf_dma, GFP_KERNEL);
		if (!ha->exchoffld_buf) {
			ql_log_pci(ql_log_fatal, ha->pdev, 0xd013,
			"Failed to allocate memory for Exchange Offload.\n");

			if (ha->max_exchg >
			    (FW_DEF_EXCHANGES_CNT + REDUCE_EXCHANGES_CNT)) {
				ha->max_exchg -= REDUCE_EXCHANGES_CNT;
			} else if (ha->max_exchg >
			    (FW_DEF_EXCHANGES_CNT + 512)) {
				ha->max_exchg -= 512;
			} else {
				ha->flags.exchoffld_enabled = 0;
				ql_log_pci(ql_log_fatal, ha->pdev, 0xd013,
				    "Disabling Exchange offload due to lack of memory\n");
			}
			ha->exchoffld_size = 0;

			return -ENOMEM;
		}
	} else if (!ha->exchoffld_buf || (actual_cnt <= FW_DEF_EXCHANGES_CNT)) {
		/* pathological case */
		qla2x00_free_exchoffld_buffer(ha);
		ha->exchoffld_size = 0;
		ha->flags.exchoffld_enabled = 0;
		ql_log(ql_log_info, vha, 0xd016,
		    "Exchange offload not enable: offld size=%d, actual count=%d entry sz=0x%x, total sz=0x%x.\n",
		    ha->exchoffld_size, actual_cnt, size, totsz);
		return 0;
	}

	/* Now configure the dma buffer */
	rval = qla_set_exchoffld_mem_cfg(vha);
	if (rval) {
		ql_log(ql_log_fatal, vha, 0xd02e,
		    "Setup exchange offload buffer ****FAILED****.\n");
		qla2x00_free_exchoffld_buffer(ha);
	} else {
		/* re-adjust number of target exchange */
		struct init_cb_81xx *icb = (struct init_cb_81xx *)ha->init_cb;

		if (qla_ini_mode_enabled(vha))
			icb->exchange_count = 0;
		else
			icb->exchange_count = cpu_to_le16(vha->ql2xexchoffld);
	}

	return rval;
}