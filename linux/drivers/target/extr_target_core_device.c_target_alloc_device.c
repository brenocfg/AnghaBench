#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct t10_pi_tuple {int dummy; } ;
struct se_lun {int /*<<< orphan*/ * lun_tpg; int /*<<< orphan*/  lun_tg_pt_md_mutex; int /*<<< orphan*/  lun_dev_link; int /*<<< orphan*/  lun_deve_list; int /*<<< orphan*/  lun_shutdown_comp; int /*<<< orphan*/  lun_se_dev; } ;
struct se_hba {int /*<<< orphan*/  hba_index; TYPE_2__* backend; } ;
struct TYPE_10__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; struct se_device* t10_dev; int /*<<< orphan*/  t10_vpd_lock; int /*<<< orphan*/  t10_vpd_list; } ;
struct TYPE_12__ {int emulate_dpo; int emulate_fua_write; int emulate_fua_read; int /*<<< orphan*/  max_write_same_len; int /*<<< orphan*/  unmap_zeroes_data; int /*<<< orphan*/  unmap_granularity_alignment; int /*<<< orphan*/  unmap_granularity; int /*<<< orphan*/  max_unmap_block_desc_count; int /*<<< orphan*/  max_unmap_lba_count; int /*<<< orphan*/  emulate_rest_reord; int /*<<< orphan*/  is_nonrot; int /*<<< orphan*/  force_pr_aptpl; int /*<<< orphan*/  enforce_pr_isids; int /*<<< orphan*/  pi_prot_type; int /*<<< orphan*/  emulate_pr; int /*<<< orphan*/  emulate_3pc; int /*<<< orphan*/  emulate_caw; int /*<<< orphan*/  emulate_tpws; int /*<<< orphan*/  emulate_tpu; int /*<<< orphan*/  emulate_tas; int /*<<< orphan*/  emulate_ua_intlck_ctrl; int /*<<< orphan*/  emulate_write_cache; int /*<<< orphan*/  emulate_model_alias; struct se_device* da_dev; } ;
struct TYPE_11__ {struct se_device* t10_dev; int /*<<< orphan*/  lba_map_lock; int /*<<< orphan*/  lba_map_list; int /*<<< orphan*/  tg_pt_gps_lock; int /*<<< orphan*/  tg_pt_gps_list; } ;
struct TYPE_9__ {int /*<<< orphan*/  aptpl_reg_lock; int /*<<< orphan*/  registration_lock; int /*<<< orphan*/  aptpl_reg_list; int /*<<< orphan*/  registration_list; } ;
struct se_device {int prot_length; TYPE_1__* transport; TYPE_4__ t10_wwn; struct se_lun xcopy_lun; TYPE_6__ dev_attrib; TYPE_5__ t10_alua; TYPE_3__ t10_pr; int /*<<< orphan*/  caw_sem; int /*<<< orphan*/  qf_cmd_lock; int /*<<< orphan*/  se_tmr_lock; int /*<<< orphan*/  se_port_lock; int /*<<< orphan*/  dev_reservation_lock; int /*<<< orphan*/  delayed_cmd_lock; int /*<<< orphan*/  execute_task_lock; int /*<<< orphan*/  qf_cmd_list; int /*<<< orphan*/  state_list; int /*<<< orphan*/  delayed_cmd_list; int /*<<< orphan*/  dev_tmr_list; int /*<<< orphan*/  dev_sep_list; int /*<<< orphan*/  hba_index; struct se_hba* se_hba; } ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {char* inquiry_prod; char* inquiry_rev; struct se_device* (* alloc_device ) (struct se_hba*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DA_EMULATE_3PC ; 
 int /*<<< orphan*/  DA_EMULATE_CAW ; 
 int /*<<< orphan*/  DA_EMULATE_MODEL_ALIAS ; 
 int /*<<< orphan*/  DA_EMULATE_PR ; 
 int /*<<< orphan*/  DA_EMULATE_REST_REORD ; 
 int /*<<< orphan*/  DA_EMULATE_TAS ; 
 int /*<<< orphan*/  DA_EMULATE_TPU ; 
 int /*<<< orphan*/  DA_EMULATE_TPWS ; 
 int /*<<< orphan*/  DA_EMULATE_UA_INTLLCK_CTRL ; 
 int /*<<< orphan*/  DA_EMULATE_WRITE_CACHE ; 
 int /*<<< orphan*/  DA_ENFORCE_PR_ISIDS ; 
 int /*<<< orphan*/  DA_FORCE_PR_APTPL ; 
 int /*<<< orphan*/  DA_IS_NONROT ; 
 int /*<<< orphan*/  DA_MAX_UNMAP_BLOCK_DESC_COUNT ; 
 int /*<<< orphan*/  DA_MAX_UNMAP_LBA_COUNT ; 
 int /*<<< orphan*/  DA_MAX_WRITE_SAME_LEN ; 
 int /*<<< orphan*/  DA_UNMAP_GRANULARITY_ALIGNMENT_DEFAULT ; 
 int /*<<< orphan*/  DA_UNMAP_GRANULARITY_DEFAULT ; 
 int /*<<< orphan*/  DA_UNMAP_ZEROES_DATA_DEFAULT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TARGET_DIF_TYPE0_PROT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct se_device*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct se_device* stub1 (struct se_hba*,char const*) ; 
 int /*<<< orphan*/  xcopy_pt_tpg ; 

struct se_device *target_alloc_device(struct se_hba *hba, const char *name)
{
	struct se_device *dev;
	struct se_lun *xcopy_lun;

	dev = hba->backend->ops->alloc_device(hba, name);
	if (!dev)
		return NULL;

	dev->se_hba = hba;
	dev->transport = hba->backend->ops;
	dev->prot_length = sizeof(struct t10_pi_tuple);
	dev->hba_index = hba->hba_index;

	INIT_LIST_HEAD(&dev->dev_sep_list);
	INIT_LIST_HEAD(&dev->dev_tmr_list);
	INIT_LIST_HEAD(&dev->delayed_cmd_list);
	INIT_LIST_HEAD(&dev->state_list);
	INIT_LIST_HEAD(&dev->qf_cmd_list);
	spin_lock_init(&dev->execute_task_lock);
	spin_lock_init(&dev->delayed_cmd_lock);
	spin_lock_init(&dev->dev_reservation_lock);
	spin_lock_init(&dev->se_port_lock);
	spin_lock_init(&dev->se_tmr_lock);
	spin_lock_init(&dev->qf_cmd_lock);
	sema_init(&dev->caw_sem, 1);
	INIT_LIST_HEAD(&dev->t10_wwn.t10_vpd_list);
	spin_lock_init(&dev->t10_wwn.t10_vpd_lock);
	INIT_LIST_HEAD(&dev->t10_pr.registration_list);
	INIT_LIST_HEAD(&dev->t10_pr.aptpl_reg_list);
	spin_lock_init(&dev->t10_pr.registration_lock);
	spin_lock_init(&dev->t10_pr.aptpl_reg_lock);
	INIT_LIST_HEAD(&dev->t10_alua.tg_pt_gps_list);
	spin_lock_init(&dev->t10_alua.tg_pt_gps_lock);
	INIT_LIST_HEAD(&dev->t10_alua.lba_map_list);
	spin_lock_init(&dev->t10_alua.lba_map_lock);

	dev->t10_wwn.t10_dev = dev;
	dev->t10_alua.t10_dev = dev;

	dev->dev_attrib.da_dev = dev;
	dev->dev_attrib.emulate_model_alias = DA_EMULATE_MODEL_ALIAS;
	dev->dev_attrib.emulate_dpo = 1;
	dev->dev_attrib.emulate_fua_write = 1;
	dev->dev_attrib.emulate_fua_read = 1;
	dev->dev_attrib.emulate_write_cache = DA_EMULATE_WRITE_CACHE;
	dev->dev_attrib.emulate_ua_intlck_ctrl = DA_EMULATE_UA_INTLLCK_CTRL;
	dev->dev_attrib.emulate_tas = DA_EMULATE_TAS;
	dev->dev_attrib.emulate_tpu = DA_EMULATE_TPU;
	dev->dev_attrib.emulate_tpws = DA_EMULATE_TPWS;
	dev->dev_attrib.emulate_caw = DA_EMULATE_CAW;
	dev->dev_attrib.emulate_3pc = DA_EMULATE_3PC;
	dev->dev_attrib.emulate_pr = DA_EMULATE_PR;
	dev->dev_attrib.pi_prot_type = TARGET_DIF_TYPE0_PROT;
	dev->dev_attrib.enforce_pr_isids = DA_ENFORCE_PR_ISIDS;
	dev->dev_attrib.force_pr_aptpl = DA_FORCE_PR_APTPL;
	dev->dev_attrib.is_nonrot = DA_IS_NONROT;
	dev->dev_attrib.emulate_rest_reord = DA_EMULATE_REST_REORD;
	dev->dev_attrib.max_unmap_lba_count = DA_MAX_UNMAP_LBA_COUNT;
	dev->dev_attrib.max_unmap_block_desc_count =
		DA_MAX_UNMAP_BLOCK_DESC_COUNT;
	dev->dev_attrib.unmap_granularity = DA_UNMAP_GRANULARITY_DEFAULT;
	dev->dev_attrib.unmap_granularity_alignment =
				DA_UNMAP_GRANULARITY_ALIGNMENT_DEFAULT;
	dev->dev_attrib.unmap_zeroes_data =
				DA_UNMAP_ZEROES_DATA_DEFAULT;
	dev->dev_attrib.max_write_same_len = DA_MAX_WRITE_SAME_LEN;

	xcopy_lun = &dev->xcopy_lun;
	rcu_assign_pointer(xcopy_lun->lun_se_dev, dev);
	init_completion(&xcopy_lun->lun_shutdown_comp);
	INIT_LIST_HEAD(&xcopy_lun->lun_deve_list);
	INIT_LIST_HEAD(&xcopy_lun->lun_dev_link);
	mutex_init(&xcopy_lun->lun_tg_pt_md_mutex);
	xcopy_lun->lun_tpg = &xcopy_pt_tpg;

	/* Preload the default INQUIRY const values */
	strlcpy(dev->t10_wwn.vendor, "LIO-ORG", sizeof(dev->t10_wwn.vendor));
	strlcpy(dev->t10_wwn.model, dev->transport->inquiry_prod,
		sizeof(dev->t10_wwn.model));
	strlcpy(dev->t10_wwn.revision, dev->transport->inquiry_rev,
		sizeof(dev->t10_wwn.revision));

	return dev;
}