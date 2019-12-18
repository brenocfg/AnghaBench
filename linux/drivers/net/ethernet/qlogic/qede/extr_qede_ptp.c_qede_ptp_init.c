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
struct TYPE_5__ {int mult; scalar_t__ shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  read; } ;
struct qede_ptp {TYPE_2__ cc; int /*<<< orphan*/  tc; int /*<<< orphan*/  work; TYPE_1__* ops; int /*<<< orphan*/  lock; } ;
struct qede_dev {int /*<<< orphan*/  cdev; struct qede_ptp* ptp; } ;
struct TYPE_4__ {int (* enable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CYCLECOUNTER_MASK (int) ; 
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qede_ptp_read_cc ; 
 int /*<<< orphan*/  qede_ptp_task ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_ptp_init(struct qede_dev *edev, bool init_tc)
{
	struct qede_ptp *ptp;
	int rc;

	ptp = edev->ptp;
	if (!ptp)
		return -EINVAL;

	spin_lock_init(&ptp->lock);

	/* Configure PTP in HW */
	rc = ptp->ops->enable(edev->cdev);
	if (rc) {
		DP_INFO(edev, "PTP HW enable failed\n");
		return rc;
	}

	/* Init work queue for Tx timestamping */
	INIT_WORK(&ptp->work, qede_ptp_task);

	/* Init cyclecounter and timecounter. This is done only in the first
	 * load. If done in every load, PTP application will fail when doing
	 * unload / load (e.g. MTU change) while it is running.
	 */
	if (init_tc) {
		memset(&ptp->cc, 0, sizeof(ptp->cc));
		ptp->cc.read = qede_ptp_read_cc;
		ptp->cc.mask = CYCLECOUNTER_MASK(64);
		ptp->cc.shift = 0;
		ptp->cc.mult = 1;

		timecounter_init(&ptp->tc, &ptp->cc,
				 ktime_to_ns(ktime_get_real()));
	}

	return rc;
}