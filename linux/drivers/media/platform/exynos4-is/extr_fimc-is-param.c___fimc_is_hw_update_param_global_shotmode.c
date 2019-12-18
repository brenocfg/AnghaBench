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
struct param_global_shotmode {int dummy; } ;
struct fimc_is {size_t config_index; TYPE_5__* config; TYPE_3__* is_p_region; } ;
struct TYPE_9__ {struct param_global_shotmode shotmode; } ;
struct TYPE_10__ {TYPE_4__ global; } ;
struct TYPE_6__ {struct param_global_shotmode shotmode; } ;
struct TYPE_7__ {TYPE_1__ global; } ;
struct TYPE_8__ {TYPE_2__ parameter; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hw_param_copy (struct param_global_shotmode*,struct param_global_shotmode*) ; 

__attribute__((used)) static void __fimc_is_hw_update_param_global_shotmode(struct fimc_is *is)
{
	struct param_global_shotmode *dst, *src;

	dst = &is->is_p_region->parameter.global.shotmode;
	src = &is->config[is->config_index].global.shotmode;
	__hw_param_copy(dst, src);
}