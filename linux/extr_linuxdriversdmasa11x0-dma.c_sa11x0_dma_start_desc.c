#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sa11x0_dma_phy {int /*<<< orphan*/  num; TYPE_3__* dev; scalar_t__ sg_load; struct sa11x0_dma_desc* txd_load; } ;
struct TYPE_5__ {int /*<<< orphan*/  cookie; } ;
struct TYPE_8__ {TYPE_1__ tx; int /*<<< orphan*/  node; } ;
struct sa11x0_dma_desc {int /*<<< orphan*/  ddar; TYPE_4__ vd; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_2__ slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sa11x0_dma_start_desc(struct sa11x0_dma_phy *p, struct sa11x0_dma_desc *txd)
{
	list_del(&txd->vd.node);
	p->txd_load = txd;
	p->sg_load = 0;

	dev_vdbg(p->dev->slave.dev, "pchan %u: txd %p[%x]: starting: DDAR:%x\n",
		p->num, &txd->vd, txd->vd.tx.cookie, txd->ddar);
}