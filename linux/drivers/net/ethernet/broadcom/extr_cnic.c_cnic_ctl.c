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
typedef  size_t u32 ;
struct cnic_local {struct cnic_context* ctx_tbl; int /*<<< orphan*/  delete_task; int /*<<< orphan*/  cnic_local_flags; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; struct cnic_local* cnic_priv; } ;
struct cnic_ctl_completion {int /*<<< orphan*/  error; int /*<<< orphan*/  cid; } ;
struct TYPE_2__ {struct cnic_ctl_completion comp; } ;
struct cnic_ctl_info {int cmd; TYPE_1__ data; } ;
struct cnic_context {int wait_cond; int /*<<< orphan*/  waitq; int /*<<< orphan*/  ctx_flags; } ;

/* Variables and functions */
 size_t BNX2X_SW_CID (int /*<<< orphan*/ ) ; 
#define  CNIC_CTL_COMPLETION_CMD 133 
#define  CNIC_CTL_FCOE_STATS_GET_CMD 132 
#define  CNIC_CTL_ISCSI_STATS_GET_CMD 131 
#define  CNIC_CTL_START_CMD 130 
#define  CNIC_CTL_STOP_CMD 129 
#define  CNIC_CTL_STOP_ISCSI_CMD 128 
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int /*<<< orphan*/  CNIC_LCL_FL_STOP_ISCSI ; 
 int CNIC_ULP_FCOE ; 
 int CNIC_ULP_ISCSI ; 
 int /*<<< orphan*/  CTX_FL_CID_ERROR ; 
 int EINVAL ; 
 int /*<<< orphan*/  cnic_copy_ulp_stats (struct cnic_dev*,int) ; 
 int /*<<< orphan*/  cnic_get_l5_cid (struct cnic_local*,size_t,size_t*) ; 
 int /*<<< orphan*/  cnic_hold (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_put (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_start_hw (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_stop_hw (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_ulp_start (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_ulp_stop (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_wq ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_ctl(void *data, struct cnic_ctl_info *info)
{
	struct cnic_dev *dev = data;
	int ulp_type = CNIC_ULP_ISCSI;

	switch (info->cmd) {
	case CNIC_CTL_STOP_CMD:
		cnic_hold(dev);

		cnic_ulp_stop(dev);
		cnic_stop_hw(dev);

		cnic_put(dev);
		break;
	case CNIC_CTL_START_CMD:
		cnic_hold(dev);

		if (!cnic_start_hw(dev))
			cnic_ulp_start(dev);

		cnic_put(dev);
		break;
	case CNIC_CTL_STOP_ISCSI_CMD: {
		struct cnic_local *cp = dev->cnic_priv;
		set_bit(CNIC_LCL_FL_STOP_ISCSI, &cp->cnic_local_flags);
		queue_delayed_work(cnic_wq, &cp->delete_task, 0);
		break;
	}
	case CNIC_CTL_COMPLETION_CMD: {
		struct cnic_ctl_completion *comp = &info->data.comp;
		u32 cid = BNX2X_SW_CID(comp->cid);
		u32 l5_cid;
		struct cnic_local *cp = dev->cnic_priv;

		if (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
			break;

		if (cnic_get_l5_cid(cp, cid, &l5_cid) == 0) {
			struct cnic_context *ctx = &cp->ctx_tbl[l5_cid];

			if (unlikely(comp->error)) {
				set_bit(CTX_FL_CID_ERROR, &ctx->ctx_flags);
				netdev_err(dev->netdev,
					   "CID %x CFC delete comp error %x\n",
					   cid, comp->error);
			}

			ctx->wait_cond = 1;
			wake_up(&ctx->waitq);
		}
		break;
	}
	case CNIC_CTL_FCOE_STATS_GET_CMD:
		ulp_type = CNIC_ULP_FCOE;
		/* fall through */
	case CNIC_CTL_ISCSI_STATS_GET_CMD:
		cnic_hold(dev);
		cnic_copy_ulp_stats(dev, ulp_type);
		cnic_put(dev);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}