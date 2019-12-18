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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  pdev; } ;
struct intel_ntb_dev {scalar_t__ lnk_sta; TYPE_3__ ntb; TYPE_2__* self_reg; scalar_t__ self_mmio; int /*<<< orphan*/  db_link_mask; TYPE_1__* reg; } ;
struct TYPE_5__ {scalar_t__ db_clear; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* db_iowrite ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GEN3_LINK_STATUS_OFFSET ; 
 int pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gen3_poll_link(struct intel_ntb_dev *ndev)
{
	u16 reg_val;
	int rc;

	ndev->reg->db_iowrite(ndev->db_link_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_clear);

	rc = pci_read_config_word(ndev->ntb.pdev,
				  GEN3_LINK_STATUS_OFFSET, &reg_val);
	if (rc)
		return 0;

	if (reg_val == ndev->lnk_sta)
		return 0;

	ndev->lnk_sta = reg_val;

	return 1;
}