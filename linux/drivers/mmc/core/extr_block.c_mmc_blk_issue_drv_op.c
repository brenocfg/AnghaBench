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
struct mmc_blk_ioc_data {int dummy; } ;
typedef  struct mmc_blk_ioc_data u8 ;
typedef  int u32 ;
struct request {int dummy; } ;
struct mmc_queue_req {int drv_op; int ioc_count; int drv_op_result; struct mmc_blk_ioc_data** drv_op_data; } ;
struct mmc_queue {struct mmc_blk_data* blkdata; struct mmc_card* card; } ;
struct TYPE_3__ {int boot_ro_lock; int /*<<< orphan*/  part_time; } ;
struct mmc_card {TYPE_1__ ext_csd; } ;
struct mmc_blk_data {TYPE_2__* disk; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXT_CSD_BOOT_WP ; 
 int EXT_CSD_BOOT_WP_B_PWR_WP_EN ; 
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
#define  MMC_DRV_OP_BOOT_WP 132 
#define  MMC_DRV_OP_GET_CARD_STATUS 131 
#define  MMC_DRV_OP_GET_EXT_CSD 130 
#define  MMC_DRV_OP_IOCTL 129 
#define  MMC_DRV_OP_IOCTL_RPMB 128 
 int __mmc_blk_ioctl_cmd (struct mmc_card*,struct mmc_blk_data*,struct mmc_blk_ioc_data*) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_blk_part_switch (struct mmc_card*,int /*<<< orphan*/ ) ; 
 int mmc_get_ext_csd (struct mmc_card*,struct mmc_blk_ioc_data**) ; 
 int mmc_send_status (struct mmc_card*,int*) ; 
 int mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 

__attribute__((used)) static void mmc_blk_issue_drv_op(struct mmc_queue *mq, struct request *req)
{
	struct mmc_queue_req *mq_rq;
	struct mmc_card *card = mq->card;
	struct mmc_blk_data *md = mq->blkdata;
	struct mmc_blk_ioc_data **idata;
	bool rpmb_ioctl;
	u8 **ext_csd;
	u32 status;
	int ret;
	int i;

	mq_rq = req_to_mmc_queue_req(req);
	rpmb_ioctl = (mq_rq->drv_op == MMC_DRV_OP_IOCTL_RPMB);

	switch (mq_rq->drv_op) {
	case MMC_DRV_OP_IOCTL:
	case MMC_DRV_OP_IOCTL_RPMB:
		idata = mq_rq->drv_op_data;
		for (i = 0, ret = 0; i < mq_rq->ioc_count; i++) {
			ret = __mmc_blk_ioctl_cmd(card, md, idata[i]);
			if (ret)
				break;
		}
		/* Always switch back to main area after RPMB access */
		if (rpmb_ioctl)
			mmc_blk_part_switch(card, 0);
		break;
	case MMC_DRV_OP_BOOT_WP:
		ret = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BOOT_WP,
				 card->ext_csd.boot_ro_lock |
				 EXT_CSD_BOOT_WP_B_PWR_WP_EN,
				 card->ext_csd.part_time);
		if (ret)
			pr_err("%s: Locking boot partition ro until next power on failed: %d\n",
			       md->disk->disk_name, ret);
		else
			card->ext_csd.boot_ro_lock |=
				EXT_CSD_BOOT_WP_B_PWR_WP_EN;
		break;
	case MMC_DRV_OP_GET_CARD_STATUS:
		ret = mmc_send_status(card, &status);
		if (!ret)
			ret = status;
		break;
	case MMC_DRV_OP_GET_EXT_CSD:
		ext_csd = mq_rq->drv_op_data;
		ret = mmc_get_ext_csd(card, ext_csd);
		break;
	default:
		pr_err("%s: unknown driver specific operation\n",
		       md->disk->disk_name);
		ret = -EINVAL;
		break;
	}
	mq_rq->drv_op_result = ret;
	blk_mq_end_request(req, ret ? BLK_STS_IOERR : BLK_STS_OK);
}