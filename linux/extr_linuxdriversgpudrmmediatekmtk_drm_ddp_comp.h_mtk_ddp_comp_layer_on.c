#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_ddp_comp {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* layer_on ) (struct mtk_ddp_comp*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mtk_ddp_comp*,unsigned int) ; 

__attribute__((used)) static inline void mtk_ddp_comp_layer_on(struct mtk_ddp_comp *comp,
					 unsigned int idx)
{
	if (comp->funcs && comp->funcs->layer_on)
		comp->funcs->layer_on(comp, idx);
}