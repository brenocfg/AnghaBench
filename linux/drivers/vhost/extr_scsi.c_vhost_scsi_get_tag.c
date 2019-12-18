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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vhost_virtqueue {int dummy; } ;
struct vhost_scsi_tpg {struct vhost_scsi_nexus* tpg_nexus; } ;
struct vhost_scsi_nexus {struct se_session* tvn_se_sess; } ;
struct TYPE_2__ {int map_tag; int map_cpu; } ;
struct vhost_scsi_cmd {int tvc_data_direction; int /*<<< orphan*/  tvc_cdb; int /*<<< orphan*/  inflight; struct vhost_scsi_nexus* tvc_nexus; int /*<<< orphan*/  tvc_exp_data_len; int /*<<< orphan*/  tvc_task_attr; int /*<<< orphan*/  tvc_lun; int /*<<< orphan*/  tvc_tag; TYPE_1__ tvc_se_cmd; struct page** tvc_upages; struct scatterlist* tvc_prot_sgl; struct scatterlist* tvc_sgl; } ;
struct se_session {scalar_t__ sess_cmd_map; int /*<<< orphan*/  sess_tag_pool; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct vhost_scsi_cmd* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VHOST_SCSI_MAX_CDB_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vhost_scsi_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sbitmap_queue_get (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vhost_scsi_get_inflight (struct vhost_virtqueue*) ; 

__attribute__((used)) static struct vhost_scsi_cmd *
vhost_scsi_get_tag(struct vhost_virtqueue *vq, struct vhost_scsi_tpg *tpg,
		   unsigned char *cdb, u64 scsi_tag, u16 lun, u8 task_attr,
		   u32 exp_data_len, int data_direction)
{
	struct vhost_scsi_cmd *cmd;
	struct vhost_scsi_nexus *tv_nexus;
	struct se_session *se_sess;
	struct scatterlist *sg, *prot_sg;
	struct page **pages;
	int tag, cpu;

	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus) {
		pr_err("Unable to locate active struct vhost_scsi_nexus\n");
		return ERR_PTR(-EIO);
	}
	se_sess = tv_nexus->tvn_se_sess;

	tag = sbitmap_queue_get(&se_sess->sess_tag_pool, &cpu);
	if (tag < 0) {
		pr_err("Unable to obtain tag for vhost_scsi_cmd\n");
		return ERR_PTR(-ENOMEM);
	}

	cmd = &((struct vhost_scsi_cmd *)se_sess->sess_cmd_map)[tag];
	sg = cmd->tvc_sgl;
	prot_sg = cmd->tvc_prot_sgl;
	pages = cmd->tvc_upages;
	memset(cmd, 0, sizeof(*cmd));
	cmd->tvc_sgl = sg;
	cmd->tvc_prot_sgl = prot_sg;
	cmd->tvc_upages = pages;
	cmd->tvc_se_cmd.map_tag = tag;
	cmd->tvc_se_cmd.map_cpu = cpu;
	cmd->tvc_tag = scsi_tag;
	cmd->tvc_lun = lun;
	cmd->tvc_task_attr = task_attr;
	cmd->tvc_exp_data_len = exp_data_len;
	cmd->tvc_data_direction = data_direction;
	cmd->tvc_nexus = tv_nexus;
	cmd->inflight = vhost_scsi_get_inflight(vq);

	memcpy(cmd->tvc_cdb, cdb, VHOST_SCSI_MAX_CDB_SIZE);

	return cmd;
}