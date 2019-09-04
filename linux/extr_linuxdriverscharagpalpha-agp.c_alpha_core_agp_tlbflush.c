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
struct agp_memory {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hose; } ;
typedef  TYPE_1__ alpha_agp_info ;
struct TYPE_6__ {TYPE_1__* dev_private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* mv_pci_tbi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_3__* agp_bridge ; 
 TYPE_2__ alpha_mv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void alpha_core_agp_tlbflush(struct agp_memory *mem)
{
	alpha_agp_info *agp = agp_bridge->dev_private_data;
	alpha_mv.mv_pci_tbi(agp->hose, 0, -1);
}