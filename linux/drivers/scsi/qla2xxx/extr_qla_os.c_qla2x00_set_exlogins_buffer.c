#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct qla_hw_data {scalar_t__ exlogin_size; int /*<<< orphan*/  exlogin_buf_dma; TYPE_5__* pdev; int /*<<< orphan*/  exlogin_buf; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_EXLOGIN_OFFLD_CAPABLE (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ql2xexlogins ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_pci (int /*<<< orphan*/ ,TYPE_5__*,int,char*) ; 
 int /*<<< orphan*/  qla2x00_free_exlogin_buffer (struct qla_hw_data*) ; 
 int qla_get_exlogin_status (TYPE_1__*,scalar_t__*,scalar_t__*) ; 
 int qla_set_exlogin_mem_cfg (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
qla2x00_set_exlogins_buffer(scsi_qla_host_t *vha)
{
	int rval;
	uint16_t	size, max_cnt, temp;
	struct qla_hw_data *ha = vha->hw;

	/* Return if we don't need to alloacate any extended logins */
	if (!ql2xexlogins)
		return QLA_SUCCESS;

	if (!IS_EXLOGIN_OFFLD_CAPABLE(ha))
		return QLA_SUCCESS;

	ql_log(ql_log_info, vha, 0xd021, "EXLOGIN count: %d.\n", ql2xexlogins);
	max_cnt = 0;
	rval = qla_get_exlogin_status(vha, &size, &max_cnt);
	if (rval != QLA_SUCCESS) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0xd029,
		    "Failed to get exlogin status.\n");
		return rval;
	}

	temp = (ql2xexlogins > max_cnt) ? max_cnt : ql2xexlogins;
	temp *= size;

	if (temp != ha->exlogin_size) {
		qla2x00_free_exlogin_buffer(ha);
		ha->exlogin_size = temp;

		ql_log(ql_log_info, vha, 0xd024,
		    "EXLOGIN: max_logins=%d, portdb=0x%x, total=%d.\n",
		    max_cnt, size, temp);

		ql_log(ql_log_info, vha, 0xd025,
		    "EXLOGIN: requested size=0x%x\n", ha->exlogin_size);

		/* Get consistent memory for extended logins */
		ha->exlogin_buf = dma_alloc_coherent(&ha->pdev->dev,
			ha->exlogin_size, &ha->exlogin_buf_dma, GFP_KERNEL);
		if (!ha->exlogin_buf) {
			ql_log_pci(ql_log_fatal, ha->pdev, 0xd02a,
		    "Failed to allocate memory for exlogin_buf_dma.\n");
			return -ENOMEM;
		}
	}

	/* Now configure the dma buffer */
	rval = qla_set_exlogin_mem_cfg(vha, ha->exlogin_buf_dma);
	if (rval) {
		ql_log(ql_log_fatal, vha, 0xd033,
		    "Setup extended login buffer  ****FAILED****.\n");
		qla2x00_free_exlogin_buffer(ha);
	}

	return rval;
}