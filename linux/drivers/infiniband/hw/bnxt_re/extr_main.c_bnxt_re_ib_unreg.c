#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/  creq_ring_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  fw_id; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;
struct bnxt_re_dev {int /*<<< orphan*/  flags; TYPE_3__ rcfw; int /*<<< orphan*/  chip_ctx; TYPE_4__ qplib_ctx; TYPE_2__* en_dev; int /*<<< orphan*/  worker; } ;
struct TYPE_8__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_RE_FLAG_GOT_MSIX ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_IBDEV_REGISTERED ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_NETDEV_REGISTERED ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_QOS_WORK_REG ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_RCFW_CHANNEL_EN ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_RESOURCES_ALLOCATED ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_RESOURCES_INITIALIZED ; 
 int bnxt_qplib_deinit_rcfw (TYPE_3__*) ; 
 int /*<<< orphan*/  bnxt_qplib_disable_rcfw_channel (TYPE_3__*) ; 
 int /*<<< orphan*/  bnxt_qplib_free_ctx (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  bnxt_qplib_free_rcfw_channel (TYPE_3__*) ; 
 int /*<<< orphan*/  bnxt_qplib_get_ring_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_cleanup_res (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_destroy_chip_ctx (struct bnxt_re_dev*) ; 
 int bnxt_re_free_msix (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_free_res (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_net_ring_free (struct bnxt_re_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_net_stats_ctx_free (struct bnxt_re_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_unregister_ib (struct bnxt_re_dev*) ; 
 int bnxt_re_unregister_netdev (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_re_ib_unreg(struct bnxt_re_dev *rdev)
{
	u8 type;
	int rc;

	if (test_and_clear_bit(BNXT_RE_FLAG_IBDEV_REGISTERED, &rdev->flags)) {
		/* Cleanup ib dev */
		bnxt_re_unregister_ib(rdev);
	}
	if (test_and_clear_bit(BNXT_RE_FLAG_QOS_WORK_REG, &rdev->flags))
		cancel_delayed_work_sync(&rdev->worker);

	if (test_and_clear_bit(BNXT_RE_FLAG_RESOURCES_INITIALIZED,
			       &rdev->flags))
		bnxt_re_cleanup_res(rdev);
	if (test_and_clear_bit(BNXT_RE_FLAG_RESOURCES_ALLOCATED, &rdev->flags))
		bnxt_re_free_res(rdev);

	if (test_and_clear_bit(BNXT_RE_FLAG_RCFW_CHANNEL_EN, &rdev->flags)) {
		rc = bnxt_qplib_deinit_rcfw(&rdev->rcfw);
		if (rc)
			dev_warn(rdev_to_dev(rdev),
				 "Failed to deinitialize RCFW: %#x", rc);
		bnxt_re_net_stats_ctx_free(rdev, rdev->qplib_ctx.stats.fw_id);
		bnxt_qplib_free_ctx(rdev->en_dev->pdev, &rdev->qplib_ctx);
		bnxt_qplib_disable_rcfw_channel(&rdev->rcfw);
		type = bnxt_qplib_get_ring_type(&rdev->chip_ctx);
		bnxt_re_net_ring_free(rdev, rdev->rcfw.creq_ring_id, type);
		bnxt_qplib_free_rcfw_channel(&rdev->rcfw);
	}
	if (test_and_clear_bit(BNXT_RE_FLAG_GOT_MSIX, &rdev->flags)) {
		rc = bnxt_re_free_msix(rdev);
		if (rc)
			dev_warn(rdev_to_dev(rdev),
				 "Failed to free MSI-X vectors: %#x", rc);
	}

	bnxt_re_destroy_chip_ctx(rdev);
	if (test_and_clear_bit(BNXT_RE_FLAG_NETDEV_REGISTERED, &rdev->flags)) {
		rc = bnxt_re_unregister_netdev(rdev);
		if (rc)
			dev_warn(rdev_to_dev(rdev),
				 "Failed to unregister with netdev: %#x", rc);
	}
}