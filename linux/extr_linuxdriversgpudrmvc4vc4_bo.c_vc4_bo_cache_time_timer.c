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
struct TYPE_3__ {int /*<<< orphan*/  time_work; } ;
struct vc4_dev {TYPE_1__ bo_cache; } ;
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  time_timer; } ;

/* Variables and functions */
 TYPE_2__ bo_cache ; 
 struct vc4_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct vc4_dev* vc4 ; 

__attribute__((used)) static void vc4_bo_cache_time_timer(struct timer_list *t)
{
	struct vc4_dev *vc4 = from_timer(vc4, t, bo_cache.time_timer);

	schedule_work(&vc4->bo_cache.time_work);
}