#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  creq_ring_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  fw_id; } ;
struct TYPE_12__ {TYPE_2__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct bnxt_re_dev {int /*<<< orphan*/  flags; TYPE_4__ rcfw; TYPE_5__ qplib_ctx; TYPE_3__* en_dev; int /*<<< orphan*/  worker; TYPE_1__ ibdev; } ;
struct TYPE_10__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_GOT_MSIX ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_IBDEV_REGISTERED ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_NETDEV_REGISTERED ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_QOS_WORK_REG ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_RCFW_CHANNEL_EN ; 
 int bnxt_qplib_deinit_rcfw (TYPE_4__*) ; 
 int /*<<< orphan*/  bnxt_qplib_disable_rcfw_channel (TYPE_4__*) ; 
 int /*<<< orphan*/  bnxt_qplib_free_ctx (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  bnxt_qplib_free_rcfw_channel (TYPE_4__*) ; 
 int /*<<< orphan*/ * bnxt_re_attributes ; 
 int /*<<< orphan*/  bnxt_re_cleanup_res (struct bnxt_re_dev*) ; 
 int bnxt_re_free_msix (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_free_res (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_net_ring_free (struct bnxt_re_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_net_stats_ctx_free (struct bnxt_re_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_unregister_ib (struct bnxt_re_dev*) ; 
 int bnxt_re_unregister_netdev (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_re_ib_unreg(struct bnxt_re_dev *rdev)
{
	int i, rc;

	if (test_and_clear_bit(BNXT_RE_FLAG_IBDEV_REGISTERED, &rdev->flags)) {
		for (i = 0; i < ARRAY_SIZE(bnxt_re_attributes); i++)
			device_remove_file(&rdev->ibdev.dev,
					   bnxt_re_attributes[i]);
		/* Cleanup ib dev */
		bnxt_re_unregister_ib(rdev);
	}
	if (test_and_clear_bit(BNXT_RE_FLAG_QOS_WORK_REG, &rdev->flags))
		cancel_delayed_work(&rdev->worker);

	bnxt_re_cleanup_res(rdev);
	bnxt_re_free_res(rdev);

	if (test_and_clear_bit(BNXT_RE_FLAG_RCFW_CHANNEL_EN, &rdev->flags)) {
		rc = bnxt_qplib_deinit_rcfw(&rdev->rcfw);
		if (rc)
			dev_warn(rdev_to_dev(rdev),
				 "Failed to deinitialize RCFW: %#x", rc);
		bnxt_re_net_stats_ctx_free(rdev, rdev->qplib_ctx.stats.fw_id);
		bnxt_qplib_free_ctx(rdev->en_dev->pdev, &rdev->qplib_ctx);
		bnxt_qplib_disable_rcfw_channel(&rdev->rcfw);
		bnxt_re_net_ring_free(rdev, rdev->rcfw.creq_ring_id);
		bnxt_qplib_free_rcfw_channel(&rdev->rcfw);
	}
	if (test_and_clear_bit(BNXT_RE_FLAG_GOT_MSIX, &rdev->flags)) {
		rc = bnxt_re_free_msix(rdev);
		if (rc)
			dev_warn(rdev_to_dev(rdev),
				 "Failed to free MSI-X vectors: %#x", rc);
	}
	if (test_and_clear_bit(BNXT_RE_FLAG_NETDEV_REGISTERED, &rdev->flags)) {
		rc = bnxt_re_unregister_netdev(rdev);
		if (rc)
			dev_warn(rdev_to_dev(rdev),
				 "Failed to unregister with netdev: %#x", rc);
	}
}