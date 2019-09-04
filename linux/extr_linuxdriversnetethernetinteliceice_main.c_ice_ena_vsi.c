#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {TYPE_2__* vsw; int /*<<< orphan*/  vsi_num; TYPE_1__* back; TYPE_5__* netdev; int /*<<< orphan*/  state; } ;
struct TYPE_11__ {TYPE_3__* netdev_ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* ndo_open ) (TYPE_5__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  sw_id; } ;
struct TYPE_7__ {TYPE_4__* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_NEEDS_RESTART ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_vsi_open (struct ice_vsi*) ; 
 scalar_t__ netif_running (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_ena_vsi(struct ice_vsi *vsi)
{
	if (!test_and_clear_bit(__ICE_NEEDS_RESTART, vsi->state))
		return;

	if (vsi->netdev && netif_running(vsi->netdev))
		vsi->netdev->netdev_ops->ndo_open(vsi->netdev);
	else if (ice_vsi_open(vsi))
		/* this clears the DOWN bit */
		dev_dbg(&vsi->back->pdev->dev, "Failed open VSI 0x%04X on switch 0x%04X\n",
			vsi->vsi_num, vsi->vsw->sw_id);
}