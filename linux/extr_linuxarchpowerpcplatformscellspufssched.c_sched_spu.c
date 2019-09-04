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
struct spu {size_t node; TYPE_1__* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  list_mutex; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SPU_CREATE_NOSCHED ; 
 TYPE_2__* cbe_spu_info ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int sched_spu(struct spu *spu)
{
	BUG_ON(!mutex_is_locked(&cbe_spu_info[spu->node].list_mutex));

	return (!spu->ctx || !(spu->ctx->flags & SPU_CREATE_NOSCHED));
}