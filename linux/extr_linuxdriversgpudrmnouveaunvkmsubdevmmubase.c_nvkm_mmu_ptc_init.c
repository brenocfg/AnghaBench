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
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  mutex; } ;
struct nvkm_mmu {TYPE_2__ ptp; TYPE_1__ ptc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvkm_mmu_ptc_init(struct nvkm_mmu *mmu)
{
	mutex_init(&mmu->ptc.mutex);
	INIT_LIST_HEAD(&mmu->ptc.list);
	mutex_init(&mmu->ptp.mutex);
	INIT_LIST_HEAD(&mmu->ptp.list);
}