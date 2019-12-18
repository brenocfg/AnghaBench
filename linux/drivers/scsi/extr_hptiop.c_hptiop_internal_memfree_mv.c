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
struct TYPE_5__ {int /*<<< orphan*/  internal_req_phy; scalar_t__ internal_req; } ;
struct TYPE_6__ {TYPE_2__ mv; } ;
struct hptiop_hba {TYPE_3__ u; TYPE_1__* pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hptiop_internal_memfree_mv(struct hptiop_hba *hba)
{
	if (hba->u.mv.internal_req) {
		dma_free_coherent(&hba->pcidev->dev, 0x800,
			hba->u.mv.internal_req, hba->u.mv.internal_req_phy);
		return 0;
	} else
		return -1;
}