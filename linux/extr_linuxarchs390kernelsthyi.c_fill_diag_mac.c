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
struct TYPE_5__ {int /*<<< orphan*/  infmval1; int /*<<< orphan*/  infmsifl; int /*<<< orphan*/  infmdifl; int /*<<< orphan*/  infmscps; int /*<<< orphan*/  infmdcps; } ;
struct sthyi_sctns {TYPE_2__ mac; } ;
struct TYPE_6__ {int cpus; } ;
struct diag204_x_phys_block {TYPE_1__* cpus; TYPE_3__ hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  weight; int /*<<< orphan*/  ctidx; } ;

/* Variables and functions */
#define  CP 129 
 int /*<<< orphan*/  DED_WEIGHT ; 
#define  IFL 128 
 int /*<<< orphan*/  MAC_CNT_VLD ; 
 int cpu_id (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void fill_diag_mac(struct sthyi_sctns *sctns,
			  struct diag204_x_phys_block *block,
			  void *diag224_buf)
{
	int i;

	for (i = 0; i < block->hdr.cpus; i++) {
		switch (cpu_id(block->cpus[i].ctidx, diag224_buf)) {
		case CP:
			if (block->cpus[i].weight == DED_WEIGHT)
				sctns->mac.infmdcps++;
			else
				sctns->mac.infmscps++;
			break;
		case IFL:
			if (block->cpus[i].weight == DED_WEIGHT)
				sctns->mac.infmdifl++;
			else
				sctns->mac.infmsifl++;
			break;
		}
	}
	sctns->mac.infmval1 |= MAC_CNT_VLD;
}