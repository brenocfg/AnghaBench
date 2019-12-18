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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ input_buffers; } ;
struct cw1200_common {scalar_t__ hw_bufs_used; int device_can_sleep; int hw_type; int bh_error; int /*<<< orphan*/  hwbus_priv; TYPE_2__* hwbus_ops; TYPE_1__ wsm_caps; int /*<<< orphan*/  bh_rx; int /*<<< orphan*/  bh_evt_wq; int /*<<< orphan*/  bh_suspend; TYPE_3__* hw; int /*<<< orphan*/  bh_wq; scalar_t__ powersave_enabled; int /*<<< orphan*/  recent_scan; int /*<<< orphan*/  pending_frame_id; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  bh_term; int /*<<< orphan*/  bh_tx; } ;
typedef  int /*<<< orphan*/  dummy ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CW1200_BH_RESUME ; 
 int /*<<< orphan*/  CW1200_BH_RESUMED ; 
 int /*<<< orphan*/  CW1200_BH_SUSPENDED ; 
 long ERESTARTSYS ; 
 int HZ ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  ST90TDS_CONFIG_REG_ID ; 
 int /*<<< orphan*/  ST90TDS_CONTROL_REG_ID ; 
 int ST90TDS_CONT_NEXT_LEN_MASK ; 
 unsigned long WSM_CMD_LAST_CHANCE_TIMEOUT ; 
 int /*<<< orphan*/  __cw1200_irq_enable (struct cw1200_common*,int) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cw1200_bh_read_ctrl_reg (struct cw1200_common*,int*) ; 
 int cw1200_bh_rx_helper (struct cw1200_common*,int*,int*) ; 
 int cw1200_bh_tx_helper (struct cw1200_common*,int*,int*) ; 
 scalar_t__ cw1200_queue_get_xmit_timestamp (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_reg_read (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cw1200_reg_write_16 (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 long wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  wiphy_warn (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

__attribute__((used)) static int cw1200_bh(void *arg)
{
	struct cw1200_common *priv = arg;
	int rx, tx, term, suspend;
	u16 ctrl_reg = 0;
	int tx_allowed;
	int pending_tx = 0;
	int tx_burst;
	long status;
	u32 dummy;
	int ret;

	for (;;) {
		if (!priv->hw_bufs_used &&
		    priv->powersave_enabled &&
		    !priv->device_can_sleep &&
		    !atomic_read(&priv->recent_scan)) {
			status = 1 * HZ;
			pr_debug("[BH] Device wakedown. No data.\n");
			cw1200_reg_write_16(priv, ST90TDS_CONTROL_REG_ID, 0);
			priv->device_can_sleep = true;
		} else if (priv->hw_bufs_used) {
			/* Interrupt loss detection */
			status = 1 * HZ;
		} else {
			status = MAX_SCHEDULE_TIMEOUT;
		}

		/* Dummy Read for SDIO retry mechanism*/
		if ((priv->hw_type != -1) &&
		    (atomic_read(&priv->bh_rx) == 0) &&
		    (atomic_read(&priv->bh_tx) == 0))
			cw1200_reg_read(priv, ST90TDS_CONFIG_REG_ID,
					&dummy, sizeof(dummy));

		pr_debug("[BH] waiting ...\n");
		status = wait_event_interruptible_timeout(priv->bh_wq, ({
				rx = atomic_xchg(&priv->bh_rx, 0);
				tx = atomic_xchg(&priv->bh_tx, 0);
				term = atomic_xchg(&priv->bh_term, 0);
				suspend = pending_tx ?
					0 : atomic_read(&priv->bh_suspend);
				(rx || tx || term || suspend || priv->bh_error);
			}), status);

		pr_debug("[BH] - rx: %d, tx: %d, term: %d, bh_err: %d, suspend: %d, status: %ld\n",
			 rx, tx, term, suspend, priv->bh_error, status);

		/* Did an error occur? */
		if ((status < 0 && status != -ERESTARTSYS) ||
		    term || priv->bh_error) {
			break;
		}
		if (!status) {  /* wait_event timed out */
			unsigned long timestamp = jiffies;
			long timeout;
			int pending = 0;
			int i;

			/* Check to see if we have any outstanding frames */
			if (priv->hw_bufs_used && (!rx || !tx)) {
				wiphy_warn(priv->hw->wiphy,
					   "Missed interrupt? (%d frames outstanding)\n",
					   priv->hw_bufs_used);
				rx = 1;

				/* Get a timestamp of "oldest" frame */
				for (i = 0; i < 4; ++i)
					pending += cw1200_queue_get_xmit_timestamp(
						&priv->tx_queue[i],
						&timestamp,
						priv->pending_frame_id);

				/* Check if frame transmission is timed out.
				 * Add an extra second with respect to possible
				 * interrupt loss.
				 */
				timeout = timestamp +
					WSM_CMD_LAST_CHANCE_TIMEOUT +
					1 * HZ  -
					jiffies;

				/* And terminate BH thread if the frame is "stuck" */
				if (pending && timeout < 0) {
					wiphy_warn(priv->hw->wiphy,
						   "Timeout waiting for TX confirm (%d/%d pending, %ld vs %lu).\n",
						   priv->hw_bufs_used, pending,
						   timestamp, jiffies);
					break;
				}
			} else if (!priv->device_can_sleep &&
				   !atomic_read(&priv->recent_scan)) {
				pr_debug("[BH] Device wakedown. Timeout.\n");
				cw1200_reg_write_16(priv,
						    ST90TDS_CONTROL_REG_ID, 0);
				priv->device_can_sleep = true;
			}
			goto done;
		} else if (suspend) {
			pr_debug("[BH] Device suspend.\n");
			if (priv->powersave_enabled) {
				pr_debug("[BH] Device wakedown. Suspend.\n");
				cw1200_reg_write_16(priv,
						    ST90TDS_CONTROL_REG_ID, 0);
				priv->device_can_sleep = true;
			}

			atomic_set(&priv->bh_suspend, CW1200_BH_SUSPENDED);
			wake_up(&priv->bh_evt_wq);
			status = wait_event_interruptible(priv->bh_wq,
							  CW1200_BH_RESUME == atomic_read(&priv->bh_suspend));
			if (status < 0) {
				wiphy_err(priv->hw->wiphy,
					  "Failed to wait for resume: %ld.\n",
					  status);
				break;
			}
			pr_debug("[BH] Device resume.\n");
			atomic_set(&priv->bh_suspend, CW1200_BH_RESUMED);
			wake_up(&priv->bh_evt_wq);
			atomic_add(1, &priv->bh_rx);
			goto done;
		}

	rx:
		tx += pending_tx;
		pending_tx = 0;

		if (cw1200_bh_read_ctrl_reg(priv, &ctrl_reg))
			break;

		/* Don't bother trying to rx unless we have data to read */
		if (ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK) {
			ret = cw1200_bh_rx_helper(priv, &ctrl_reg, &tx);
			if (ret < 0)
				break;
			/* Double up here if there's more data.. */
			if (ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK) {
				ret = cw1200_bh_rx_helper(priv, &ctrl_reg, &tx);
				if (ret < 0)
					break;
			}
		}

	tx:
		if (tx) {
			tx = 0;

			BUG_ON(priv->hw_bufs_used > priv->wsm_caps.input_buffers);
			tx_burst = priv->wsm_caps.input_buffers - priv->hw_bufs_used;
			tx_allowed = tx_burst > 0;

			if (!tx_allowed) {
				/* Buffers full.  Ensure we process tx
				 * after we handle rx..
				 */
				pending_tx = tx;
				goto done_rx;
			}
			ret = cw1200_bh_tx_helper(priv, &pending_tx, &tx_burst);
			if (ret < 0)
				break;
			if (ret > 0) /* More to transmit */
				tx = ret;

			/* Re-read ctrl reg */
			if (cw1200_bh_read_ctrl_reg(priv, &ctrl_reg))
				break;
		}

	done_rx:
		if (priv->bh_error)
			break;
		if (ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK)
			goto rx;
		if (tx)
			goto tx;

	done:
		/* Re-enable device interrupts */
		priv->hwbus_ops->lock(priv->hwbus_priv);
		__cw1200_irq_enable(priv, 1);
		priv->hwbus_ops->unlock(priv->hwbus_priv);
	}

	/* Explicitly disable device interrupts */
	priv->hwbus_ops->lock(priv->hwbus_priv);
	__cw1200_irq_enable(priv, 0);
	priv->hwbus_ops->unlock(priv->hwbus_priv);

	if (!term) {
		pr_err("[BH] Fatal error, exiting.\n");
		priv->bh_error = 1;
		/* TODO: schedule_work(recovery) */
	}
	return 0;
}