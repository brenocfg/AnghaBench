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
struct switchtec_ntb {int /*<<< orphan*/  self_shared_dma; int /*<<< orphan*/  self_partition; int /*<<< orphan*/  mmio_peer_ctrl; TYPE_1__* stdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int config_rsvd_lut_win (struct switchtec_ntb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crosslink_is_enabled (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int switchtec_ntb_reinit_peer(struct switchtec_ntb *sndev)
{
	int rc;

	if (crosslink_is_enabled(sndev))
		return 0;

	dev_info(&sndev->stdev->dev, "reinitialize shared memory window\n");
	rc = config_rsvd_lut_win(sndev, sndev->mmio_peer_ctrl, 0,
				 sndev->self_partition,
				 sndev->self_shared_dma);
	return rc;
}