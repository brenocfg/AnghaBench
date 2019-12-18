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
typedef  int u32 ;
struct TYPE_5__ {int x; scalar_t__ y; } ;
struct TYPE_4__ {int x; scalar_t__ y; } ;
struct tcm_area {TYPE_3__* tcm; TYPE_2__ p0; TYPE_1__ p1; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_6__ {int width; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __tcm_sizeof (struct tcm_area*) ; 

__attribute__((used)) static inline s32 tcm_1d_limit(struct tcm_area *a, u32 num_pg)
{
	if (__tcm_sizeof(a) < num_pg)
		return -ENOMEM;
	if (!num_pg)
		return -EINVAL;

	a->p1.x = (a->p0.x + num_pg - 1) % a->tcm->width;
	a->p1.y = a->p0.y + ((a->p0.x + num_pg - 1) / a->tcm->width);
	return 0;
}