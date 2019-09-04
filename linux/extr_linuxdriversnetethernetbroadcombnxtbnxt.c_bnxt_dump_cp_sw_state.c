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
struct TYPE_4__ {int /*<<< orphan*/  fw_ring_id; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  cp_raw_cons; TYPE_2__ cp_ring_struct; } ;
struct bnxt_napi {int index; TYPE_1__* bp; struct bnxt_cp_ring_info cp_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_dump_cp_sw_state(struct bnxt_napi *bnapi)
{
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	int i = bnapi->index;

	netdev_info(bnapi->bp->dev, "[%d]: cp{fw_ring: %d raw_cons: %x}\n",
		    i, cpr->cp_ring_struct.fw_ring_id, cpr->cp_raw_cons);
}