#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  vp_idx; struct qla_hw_data* hw; } ;
struct qla_hw_data {int gid_list_info_size; TYPE_1__* pdev; } ;
struct gid_list_info {scalar_t__ al_pa; scalar_t__ area; scalar_t__ domain; int /*<<< orphan*/  loop_id; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {scalar_t__ al_pa; scalar_t__ area; scalar_t__ domain; } ;
typedef  TYPE_2__ be_id_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLA_SUCCESS ; 
 struct gid_list_info* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct gid_list_info*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int qla24xx_gidlist_wait (struct scsi_qla_host*,struct gid_list_info*,int /*<<< orphan*/ ,int*) ; 
 int qla2x00_gid_list_size (struct qla_hw_data*) ; 

__attribute__((used)) static int qla24xx_get_loop_id(struct scsi_qla_host *vha, be_id_t s_id,
	uint16_t *loop_id)
{
	struct qla_hw_data *ha = vha->hw;
	dma_addr_t gid_list_dma;
	struct gid_list_info *gid_list, *gid;
	int res, rc, i;
	uint16_t entries;

	gid_list = dma_alloc_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
	    &gid_list_dma, GFP_KERNEL);
	if (!gid_list) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf044,
		    "qla_target(%d): DMA Alloc failed of %u\n",
		    vha->vp_idx, qla2x00_gid_list_size(ha));
		return -ENOMEM;
	}

	/* Get list of logged in devices */
	rc = qla24xx_gidlist_wait(vha, gid_list, gid_list_dma, &entries);
	if (rc != QLA_SUCCESS) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf045,
		    "qla_target(%d): get_id_list() failed: %x\n",
		    vha->vp_idx, rc);
		res = -EBUSY;
		goto out_free_id_list;
	}

	gid = gid_list;
	res = -ENOENT;
	for (i = 0; i < entries; i++) {
		if (gid->al_pa == s_id.al_pa &&
		    gid->area == s_id.area &&
		    gid->domain == s_id.domain) {
			*loop_id = le16_to_cpu(gid->loop_id);
			res = 0;
			break;
		}
		gid = (void *)gid + ha->gid_list_info_size;
	}

out_free_id_list:
	dma_free_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
	    gid_list, gid_list_dma);
	return res;
}