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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mqd_manager {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct TYPE_3__ {int (* hqd_sdma_is_occupied ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool is_occupied_sdma(struct mqd_manager *mm, void *mqd,
		uint64_t queue_address, uint32_t pipe_id,
		uint32_t queue_id)
{
	return mm->dev->kfd2kgd->hqd_sdma_is_occupied(mm->dev->kgd, mqd);
}