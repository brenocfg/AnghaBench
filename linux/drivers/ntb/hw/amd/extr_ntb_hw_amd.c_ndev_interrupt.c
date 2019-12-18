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
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct amd_ntb_dev {int msix_vec_count; TYPE_2__ ntb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMD_DB_CNT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  amd_handle_event (struct amd_ntb_dev*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ntb_db_event (TYPE_2__*,int) ; 

__attribute__((used)) static irqreturn_t ndev_interrupt(struct amd_ntb_dev *ndev, int vec)
{
	dev_dbg(&ndev->ntb.pdev->dev, "vec %d\n", vec);

	if (vec > (AMD_DB_CNT - 1) || (ndev->msix_vec_count == 1))
		amd_handle_event(ndev, vec);

	if (vec < AMD_DB_CNT)
		ntb_db_event(&ndev->ntb, vec);

	return IRQ_HANDLED;
}