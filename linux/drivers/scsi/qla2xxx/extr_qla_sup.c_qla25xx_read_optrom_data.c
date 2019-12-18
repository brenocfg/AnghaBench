#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_hw_data {TYPE_1__* pdev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_QLA25XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA81XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 int OPTROM_BURST_DWORDS ; 
 int OPTROM_BURST_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 
 int /*<<< orphan*/  flash_data_addr (struct qla_hw_data*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 void* qla24xx_read_optrom_data (struct scsi_qla_host*,void*,int,int) ; 
 int qla2x00_dump_ram (struct scsi_qla_host*,scalar_t__,int /*<<< orphan*/ ,int) ; 

void *
qla25xx_read_optrom_data(struct scsi_qla_host *vha, void *buf,
    uint32_t offset, uint32_t length)
{
	int rval;
	dma_addr_t optrom_dma;
	void *optrom;
	uint8_t *pbuf;
	uint32_t faddr, left, burst;
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLA25XX(ha) || IS_QLA81XX(ha) || IS_QLA83XX(ha) ||
	    IS_QLA27XX(ha) || IS_QLA28XX(ha))
		goto try_fast;
	if (offset & 0xfff)
		goto slow_read;
	if (length < OPTROM_BURST_SIZE)
		goto slow_read;

try_fast:
	if (offset & 0xff)
		goto slow_read;
	optrom = dma_alloc_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
	    &optrom_dma, GFP_KERNEL);
	if (!optrom) {
		ql_log(ql_log_warn, vha, 0x00cc,
		    "Unable to allocate memory for optrom burst read (%x KB).\n",
		    OPTROM_BURST_SIZE / 1024);
		goto slow_read;
	}

	pbuf = buf;
	faddr = offset >> 2;
	left = length >> 2;
	burst = OPTROM_BURST_DWORDS;
	while (left != 0) {
		if (burst > left)
			burst = left;

		rval = qla2x00_dump_ram(vha, optrom_dma,
		    flash_data_addr(ha, faddr), burst);
		if (rval) {
			ql_log(ql_log_warn, vha, 0x00f5,
			    "Unable to burst-read optrom segment (%x/%x/%llx).\n",
			    rval, flash_data_addr(ha, faddr),
			    (unsigned long long)optrom_dma);
			ql_log(ql_log_warn, vha, 0x00f6,
			    "Reverting to slow-read.\n");

			dma_free_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
			    optrom, optrom_dma);
			goto slow_read;
		}

		memcpy(pbuf, optrom, burst * 4);

		left -= burst;
		faddr += burst;
		pbuf += burst * 4;
	}

	dma_free_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE, optrom,
	    optrom_dma);

	return buf;

slow_read:
    return qla24xx_read_optrom_data(vha, buf, offset, length);
}