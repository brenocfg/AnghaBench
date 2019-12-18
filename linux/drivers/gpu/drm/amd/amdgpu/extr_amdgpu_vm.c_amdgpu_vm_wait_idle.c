#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* bo; } ;
struct TYPE_10__ {TYPE_4__ base; } ;
struct amdgpu_vm {TYPE_5__ root; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct TYPE_8__ {TYPE_2__ tbo; } ;

/* Variables and functions */
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,long) ; 

long amdgpu_vm_wait_idle(struct amdgpu_vm *vm, long timeout)
{
	return dma_resv_wait_timeout_rcu(vm->root.base.bo->tbo.base.resv,
						   true, true, timeout);
}