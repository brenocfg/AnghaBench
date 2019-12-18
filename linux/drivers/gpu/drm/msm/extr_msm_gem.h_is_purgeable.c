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
struct TYPE_4__ {int /*<<< orphan*/  import_attach; int /*<<< orphan*/  dma_buf; TYPE_1__* dev; } ;
struct msm_gem_object {scalar_t__ madv; TYPE_2__ base; scalar_t__ sgt; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 scalar_t__ MSM_MADV_DONTNEED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool is_purgeable(struct msm_gem_object *msm_obj)
{
	WARN_ON(!mutex_is_locked(&msm_obj->base.dev->struct_mutex));
	return (msm_obj->madv == MSM_MADV_DONTNEED) && msm_obj->sgt &&
			!msm_obj->base.dma_buf && !msm_obj->base.import_attach;
}